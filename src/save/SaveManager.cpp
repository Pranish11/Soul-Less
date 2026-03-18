#include "../../include/save/SaveManager.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include "../../include/player/Player.hpp"
#include "../../include/Money/Money.hpp"
#include "../../include/inventory/Inventory.hpp"
#include "../../include/items/Place.hpp"
#include "../../include/level/Tiles.hpp"
#include "../../include/phone/phone.hpp"
#include "../../include/phone/Bank_App.hpp"

namespace {
	std::optional<std::string> getEnvVar(const char* name)
	{
#if defined(_WIN32)
		char* buffer = nullptr;
		size_t bufferSize = 0;
		const auto err = _dupenv_s(&buffer, &bufferSize, name);
		if (err != 0 || buffer == nullptr || bufferSize == 0) {
			if (buffer) {
				std::free(buffer);
			}
			return std::nullopt;
		}

		std::string value(buffer);
		std::free(buffer);
		if (value.empty()) {
			return std::nullopt;
		}
		return value;
#else
		if (const char* value = std::getenv(name); value && *value) {
			return std::string(value);
		}
		return std::nullopt;
#endif
	}

	std::optional<std::filesystem::path> preferredUserSaveDirectory()
	{
#if defined(_WIN32)
		// Prefer LOCALAPPDATA, fall back to APPDATA. Either yields a stable per-user location
		// independent of how/where the exe is launched from.
		if (const auto localAppData = getEnvVar("LOCALAPPDATA")) {
			return std::filesystem::path(*localAppData) / "Soul-Less" / "save";
		}
		if (const auto appData = getEnvVar("APPDATA")) {
			return std::filesystem::path(*appData) / "Soul-Less" / "save";
		}
#else
		if (const auto home = getEnvVar("HOME")) {
			return std::filesystem::path(*home) / ".soul-less" / "save";
		}
#endif
		return std::nullopt;
	}

	std::filesystem::path legacySaveDirectory()
	{
		// Legacy location (relative to process working directory).
		return std::filesystem::path("save");
	}
}

SaveManager::SaveManager() = default;

bool SaveManager::hasSave() const
{
	std::error_code ec;

	const std::filesystem::path preferredPath = saveFilePath();
	const std::filesystem::path legacyPath = legacySaveDirectory() / "save.json";

	if (std::filesystem::exists(preferredPath, ec) && !ec) {
		return true;
	}

	if (legacyPath != preferredPath) {
		ec.clear();
		if (std::filesystem::exists(legacyPath, ec) && !ec) {
			return true;
		}
	}

	return false;
}

std::filesystem::path SaveManager::saveDirectory() const
{
	if (const auto preferred = preferredUserSaveDirectory()) {
		return *preferred;
	}
	return legacySaveDirectory();
}

std::filesystem::path SaveManager::saveFilePath() const
{
	return saveDirectory() / "save.json";
}

nlohmann::json SaveManager::toJson(const SaveData& data)
{
	nlohmann::json j;

	// A version field makes future expansions safer (you can migrate if needed).
	j["version"] = 1;

	j["money"] = {
		{"cash", data.cash},
		{"bank", data.bankMoney}
	};

	j["player"] = {
		{"position", data.playerPosition}
	};

	j["businesses"] = {
		{"owned", data.ownedBusinesses}
	};

	j["inventory"] = nlohmann::json::object();
	j["inventory"]["slots"] = nlohmann::json::array();
	for (const SaveData::InventorySlot& slot : data.inventorySlots) {
		j["inventory"]["slots"].push_back({
			{"index", slot.index},
			{"item", slot.itemName},
			{"qty", slot.quantity}
		});
	}

	j["world"] = nlohmann::json::object();
	j["world"]["placed_items"] = nlohmann::json::array();
	for (const SaveData::PlacedItem& placed : data.placedItems) {
		j["world"]["placed_items"].push_back({
			{"item", placed.itemName},
			{"position", placed.position}
		});
	}

	return j;
}

bool SaveManager::fromJson(const nlohmann::json& j, SaveData& outData, std::string& outError)
{
	try {
	// Basic shape checks (using value() for optional fields so older/newer saves are still readable).
	const auto moneyObj = j.value("money", nlohmann::json::object());
	outData.cash = moneyObj.value("cash", 0LL);
	outData.bankMoney = moneyObj.value("bank", 0LL);

		const auto playerObj = j.value("player", nlohmann::json::object());
		outData.playerPosition = playerObj.value("position", sf::Vector2f{});

		const auto businessObj = j.value("businesses", nlohmann::json::object());
		outData.ownedBusinesses = businessObj.value("owned", std::vector<std::string>{});

		outData.inventorySlots.clear();
		const auto invObj = j.value("inventory", nlohmann::json::object());
		const auto invSlots = invObj.value("slots", nlohmann::json::array());
		if (!invSlots.is_array()) {
			outError = "inventory.slots is not an array";
			return false;
		}
		for (const auto& slotJ : invSlots) {
			SaveData::InventorySlot slot;
			slot.index = slotJ.value("index", 0);
			slot.itemName = slotJ.value("item", std::string{});
			slot.quantity = slotJ.value("qty", 0);
			outData.inventorySlots.push_back(std::move(slot));
		}

		outData.placedItems.clear();
		const auto worldObj = j.value("world", nlohmann::json::object());
		const auto placedArr = worldObj.value("placed_items", nlohmann::json::array());
		if (!placedArr.is_array()) {
			outError = "world.placed_items is not an array";
			return false;
		}
		for (const auto& placedJ : placedArr) {
			SaveData::PlacedItem placed;
			placed.itemName = placedJ.value("item", std::string{});
			placed.position = placedJ.value("position", sf::Vector2f{});
			outData.placedItems.push_back(std::move(placed));
		}

		return true;
	}
	catch (const std::exception& e) {
		outError = e.what();
		return false;
	}
}

void SaveManager::applyLoadedData(const SaveData& data,
                                 Player& player,
                                 money& wallet,
                                 Inventory& inventory,
                                 place& placer,
                                 Tiles& tilemap,
                                 phone& phoneInstance)
{
	// Money
	wallet.cash = data.cash;
	bank::Bank_Money = data.bankMoney;

	// Businesses
	phoneInstance.setOwnedBusinesses(data.ownedBusinesses);

	// Inventory
	std::vector<Inventory::SlotSaveData> invSlots;
	invSlots.reserve(data.inventorySlots.size());
	for (const SaveData::InventorySlot& slot : data.inventorySlots) {
		Inventory::SlotSaveData s;
		s.index = slot.index;
		s.itemName = slot.itemName;
		s.quantity = slot.quantity;
		invSlots.push_back(std::move(s));
	}
	inventory.setSaveSlots(invSlots);

	// Placed world items
	std::vector<place::PlacedItemSaveData> placed;
	placed.reserve(data.placedItems.size());
	for (const SaveData::PlacedItem& p : data.placedItems) {
		place::PlacedItemSaveData pi;
		pi.itemName = p.itemName;
		pi.position = p.position;
		placed.push_back(std::move(pi));
	}
	placer.setSavePlacedItems(placed, inventory, tilemap);

	// Player position
	player.setPosition(data.playerPosition);
}

SaveManager::Result SaveManager::save(const Player& player,
                                     const money& wallet,
                                     const Inventory& inventory,
                                     const place& placer,
                                     const phone& phoneInstance) const
{
	Result result;

	// Ensure folder exists.
	std::error_code ec;
	std::filesystem::create_directories(saveDirectory(), ec);
	if (ec) {
		result.ok = false;
		result.message = "Failed to create save directory: " + ec.message();
		return result;
	}

	SaveData data;
	data.cash = wallet.cash;
	data.bankMoney = bank::Bank_Money;
	data.playerPosition = player.getPosition();
	data.ownedBusinesses = phoneInstance.getOwnedBusinesses();

	// Inventory slots
	for (const Inventory::SlotSaveData& slot : inventory.getSaveSlots()) {
		SaveData::InventorySlot s;
		s.index = slot.index;
		s.itemName = slot.itemName;
		s.quantity = slot.quantity;
		data.inventorySlots.push_back(std::move(s));
	}

	// Placed items
	for (const place::PlacedItemSaveData& placed : placer.getSavePlacedItems()) {
		SaveData::PlacedItem p;
		p.itemName = placed.itemName;
		p.position = placed.position;
		data.placedItems.push_back(std::move(p));
	}

	const nlohmann::json j = toJson(data);

	std::ofstream out(saveFilePath());
	if (!out.is_open()) {
		result.ok = false;
		result.message = "Failed to open save file for writing";
		return result;
	}

	// Pretty-print with 4 spaces.
	out << j.dump(4);
	if (!out.good()) {
		result.ok = false;
		result.message = "Failed while writing save file";
		return result;
	}

	result.ok = true;
	result.message = "Saved to " + saveFilePath().string();
	return result;
}

SaveManager::Result SaveManager::load(Player& player,
                                     money& wallet,
                                     Inventory& inventory,
                                     place& placer,
                                     Tiles& tilemap,
                                     phone& phoneInstance) const
{
	Result result;

	// Ensure folder exists (so paths are consistent even before the first save).
	std::error_code ec;
	std::filesystem::create_directories(saveDirectory(), ec);

	// Prefer the stable per-user location, but also support older saves that were written
	// relative to the working directory (e.g. if the player upgraded to a build using
	// the new save path).
	const std::filesystem::path preferredPath = saveFilePath();
	const std::filesystem::path legacyPath = legacySaveDirectory() / "save.json";

	std::filesystem::path loadPath;
	if (std::filesystem::exists(preferredPath)) {
		loadPath = preferredPath;
	}
	else if (std::filesystem::exists(legacyPath)) {
		loadPath = legacyPath;
	}
	else {
		// Missing file is not an error that should crash the game.
		result.ok = false;
		result.message = "Save file not found (checked: " + preferredPath.string() + ", " + legacyPath.string() + ")";
		return result;
	}

	std::ifstream in(loadPath);
	if (!in.is_open()) {
		result.ok = false;
		result.message = "Failed to open save file for reading";
		return result;
	}

	nlohmann::json j;
	try {
		in >> j;
	}
	catch (const std::exception& e) {
		result.ok = false;
		result.message = std::string("Save file is corrupted (JSON parse error): ") + e.what();
		return result;
	}

	SaveData data;
	std::string error;
	if (!fromJson(j, data, error)) {
		result.ok = false;
		result.message = "Save file is invalid: " + error;
		return result;
	}

	applyLoadedData(data, player, wallet, inventory, placer, tilemap, phoneInstance);

	// If we loaded from the legacy location, try to migrate the save so future runs
	// (or different launch working directories) still find it.
	if (loadPath == legacyPath && preferredPath != legacyPath) {
		std::error_code migrateEc;
		std::filesystem::create_directories(preferredPath.parent_path(), migrateEc);
		if (!migrateEc) {
			std::ofstream migrated(preferredPath);
			if (migrated.is_open()) {
				migrated << j.dump(4);
			}
		}
	}

	result.ok = true;
	result.message = "Loaded from " + loadPath.string();
	return result;
}
