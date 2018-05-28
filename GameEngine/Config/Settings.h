#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include "Utility\common.hpp"
#include <map>
#include <string>
#include <fstream>

namespace GameEngine
{
	using namespace std;

	namespace UtilityM
	{

		class Settings
		{
		public:
			static Settings& getInstance()
			{
				static Settings _inst_;
				return _inst_;
			}
			Settings(Settings&) = delete;
			void operator=(Settings&) = delete;
			void loadSettings(string filename);
			void saveSettings(string filename);
			~Settings();
		private:

			string _data_file_name = "config.dat";

			Settings()
				:
				string_data(new map<string, string>{}),
				bool_data(new map<string, bool>{}),
				int_data(new map<string, int>{}),
				float_data(new map<string, float>{}),
				char_data(new map<string, char>{})
			{

			}

			map<string,string>* string_data;
			map<string, bool>* bool_data;
			map<string, int>* int_data;
			map<string, float>* float_data;
			map<string, char>* char_data;
			
			template <typename T>
			T operator[](const string& key)
			{
				using _type = typeid(T).hash_code();
				switch (_type)
				{
				case typeid(int).hash_code():
					return int_data->find(key)->second;
				case typeid(char).hash_code():
					return char_data->find(key)->second;
				case typeid(float).hash_code():
					return float_data->find(key)->second;
				}

			}

			void addSettingC(const string& key, const char val)
			{
				char_data->insert_or_assign(key, val);
			}
			const char getSettingC(const string& key) const
			{
				auto result = char_data->find(key);
				return result->second;
			}

			void addSettingF(const string& key, const float val)
			{
				float_data->insert_or_assign(key, val);
			}

			const float getSettingF(const string& key) const 
			{
				auto result = float_data->find(key);
				return result->second;
			}

			void addSettingI(const string& key, const int& val)
			{
				int_data->insert_or_assign(key, val);
			}
			const int getSettingI(const string& key) const 
			{
				auto result = int_data->find(key);
				return result->second;
			}

			void addSettingB(const string& key, const bool val)
			{
				bool_data->insert_or_assign(key, val);
			}
			const bool getSettingB(const string& key) const
			{
				auto result = bool_data->find(key);
				return result->second;
			}

			void addSettingS(const string& key, const string& val)
			{
				string_data->insert_or_assign(key, val);
			}

			const string& getSettingS(const string& key, const string& default = "") const
			{
				auto result = string_data->find(key);
				return result->second;
			}
		};
		static Settings& settings = Settings::getInstance();
	}
}
#endif /* SETTINGS_H */