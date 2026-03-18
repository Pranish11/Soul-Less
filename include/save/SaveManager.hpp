#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <vector>

#include "../json/json.hpp"

class Player;
class money;
class Inventory;
class place;
class Tiles;
class phone;

// SaveManager is responsible for turning the current game state into JSON (save)
// and restoring it back into the game objects (load).
//
// Design goals:
// - One file: save/save.json
// - Pretty-printed JSON
// - Safe failures (missing/corrupt file won't crash, and won't partially apply state)
// - Easy to extend by adding new fields to SaveData
class SaveManager {
public:
	struct Result {
		bool ok = false;
		std::string message;
	};

	SaveManager();

	// Save the current game state to disk.
	Result save(const Player& player,
	            const money& wallet,
	            const Inventory& inventory,
	            const place& placer,
	            const phone& phoneInstance) const;

	// Load from disk and apply to the game state.
		Result load(Player& player,
		            money& wallet,
		            Inventory& inventory,
		            place& placer,
		            Tiles& tilemap,
		            phone& phoneInstance) const;

		// Returns true if a save file exists (preferred per-user path or legacy path).
		bool hasSave() const;

		std::filesystem::path saveDirectory() const;
		std::filesystem::path saveFilePath() const;

	private:
		struct SaveData {
			long long cash = 0;
			long long bankMoney = 0;
			std::vector<std::string> ownedBusinesses;

		// Inventory is saved as "slots" so the layout restores exactly.
		struct InventorySlot {
			int index = 0;
			std::string itemName;
			int quantity = 0;
		};
		std::vector<InventorySlot> inventorySlots;

		struct PlacedItem {
			std::string itemName;
			sf::Vector2f position{};
		};
		std::vector<PlacedItem> placedItems;

		sf::Vector2f playerPosition{};
	};

	// Helpers for (de)serializing SaveData.
	static nlohmann::json toJson(const SaveData& data);
	static bool fromJson(const nlohmann::json& j, SaveData& outData, std::string& outError);

	// Apply data to in-memory game objects (only called after successful parse).
	static void applyLoadedData(const SaveData& data,
	                            Player& player,
	                            money& wallet,
	                            Inventory& inventory,
	                            place& placer,
	                            Tiles& tilemap,
	                            phone& phoneInstance);
};

// SFML integration: how sf::Vector2f becomes JSON and back.
// JSON example: { "x": 350.0, "y": 250.0 }
namespace nlohmann {
	template <>
	struct adl_serializer<sf::Vector2f> {
		static void to_json(json& j, const sf::Vector2f& v) {
			j = json{ {"x", v.x}, {"y", v.y} };
		}
		static void from_json(const json& j, sf::Vector2f& v) {
			// Use value() so missing fields don't throw; caller can still validate if needed.
			v.x = j.value("x", 0.f);
			v.y = j.value("y", 0.f);
		}
	};
}
