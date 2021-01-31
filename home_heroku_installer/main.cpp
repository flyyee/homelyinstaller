#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

int main() {
	// TODO: notify user about heroku login
	// TODO: replace server ip in files
	// TODO: create logs folder if not exist

	std::string my_app_name = "example-app-name";
	fstream file;

	fstream stage_file;
	std::string stage;
	stage_file.open("logs\\install_stage.txt", std::ios::in);
	stage_file >> stage;
	stage_file.close();

	const std::string log_file_names[6] = { "ins0.bat", "ins1.bat", "ins2.bat", "ins3.bat", "ins4.bat", "ins4.txt" };

	for (auto& filename : log_file_names) {
		const std::string real_filename = "logs\\" + filename;
		ifstream f(real_filename.c_str());
		if (f.good()) {
			std::remove(real_filename.c_str());
		}
	}

	if (stage.length() == 0) {
		stage = "starting";
	}
	else if (stage == "renaming") {
		goto renaming_stage;
	}
	else if (stage == "complete") {
		goto complete_stage;
	}

	std::cout << "[@@@@@] Enter your domain name (the url you will enter to visit your server). Domain names may only contain alphanumeric characters and dashes. Domain names are subject to availability. If the name has been taken, you will need to choose a different name later.\n";
	std::cout << "[@@@@@] Name: ";
	std::cin >> my_app_name;

	// TODO: make batch files hidden
	{
		file.open("logs\\ins0.bat", std::ios::out);
		string ins0 = "@echo off\necho Set-ExecutionPolicy RemoteSigned -scope CurrentUser > scoopinstall.ps1\necho iwr -useb get.scoop.sh ^| iex >> scoopinstall.ps1";
		ins0 += "\npowershell -ExecutionPolicy Bypass -File ./scoopinstall.ps1\ndel scoopinstall.ps1\nset path=%path%;C:\\Users\\%username%\\scoop\\shims";
		ins0 += "\nscoop install git\nscoop install nodejs\nscoop install python\nscoop install heroku-cli";
		file << ins0;
		file.close();
		system("logs\\ins0.bat");
		remove("logs\\ins0.bat");

		file.open("logs\\ins1.bat", std::ios::out);
		string ins1 = "@echo off\ngit clone \"https://github.com/flyyee/homely.git\"\nheroku login -i";
		file << ins1;
		file.close();
		system("logs\\ins1.bat");
		remove("logs\\ins1.bat");
		// TODO: when logging in, credentials cannot be edited

		file.open("logs\\ins2.bat", std::ios::out);
		string ins2 = "@echo off\ncd homely\nheroku create";
		file << ins2;
		file.close();
		system("logs\\ins2.bat");
		remove("logs\\ins2.bat");

		string ins3 = "@echo off\ncd homely\ngit push heroku master\nheroku ps:scale web=1";
		file.open("logs\\ins3.bat", std::ios::out);
		file << ins3;
		file.close();
		system("logs\\ins3.bat");
		remove("logs\\ins3.bat");

		stage_file.open("logs\\install_stage.txt");
		stage_file << "renaming";
		stage_file.close();
	}

renaming_stage:
	{
		bool rename_success = false;

		while (!rename_success) {
			string ins4 = "@echo off\ncd homely\nheroku apps:rename " + my_app_name + " > ../logs/ins4.txt";
			file.open("logs\\ins4.bat", std::fstream::out);
			file << ins4;
			file.close();
			system("logs\\ins4.bat");
			remove("logs\\ins4.bat");

			std::string s_buffer;
			file.open("logs\\ins4.txt");
			file >> s_buffer;
			//std::cout << s_buffer;
			file.close();
			remove("logs\\ins4.txt");

			if (s_buffer.length() > my_app_name.length()) {
				if (s_buffer == "https://" + my_app_name + ".herokuapp.com/") {
					rename_success = true;
				}
			}
			if (!rename_success) {
				std::cout << "[@@@@@] Server name has been taken. Please enter another name: ";
				std::cin >> my_app_name;
			}
		}

		string ins5 = "@echo off\ncd homely\ngit remote rm heroku\nheroku git:remote -a " + my_app_name;
		file.open("logs\\ins5.bat", std::ios::out);
		file << ins5;
		file.close();
		system("logs\\ins5.bat");
		remove("logs\\ins5.bat");
	}

complete_stage:
	std::cout << "[@@@@@] Server set-up complete!\n";
	std::cout << "[@@@@@] Server is now hosted at: https://" + my_app_name + ".herokuapp.com\n";
	stage_file.open("logs\\install_stage.txt");
	stage_file << "complete";
	stage_file.close();
	std::cin.get();

	return 0;
}
