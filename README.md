![](https://i.imgur.com/pUq7er4.png)

# Homely Installer

---

## About

This installer automates the installation of [Homely](https://github.com/flyyee/homelyinstaller). A [manual set-up guide](https://github.com/flyyee/homelyinstaller/archive/master.zip) is available on the Homely repo.

NOTE: A (free) [Heroku](https://www.heroku.com/) account is required for you to host the Homely server.

---

## Set-up

**IMPORTANT: The installer is compiled with VS2019 64bit**

1. Create a [Heroku account](https://signup.heroku.com/).
2. Download this [repository](https://github.com/flyyee/homelyinstaller/archive/master.zip) and extract its contents.
3. Run the installer located in the "Debug" folder.
4. Follow the steps in the installer.
5. When installation is complete, Homely will be located in the "Debug" folder. You can relocate the "Homely" main folder.

---

## Usage

A [guide to command line usage](https://github.com/flyyee/homely#usage) of the launcher can be found on the Homely repo.

1. Navigate to the main installation folder (called "Homely" by default).
2. Place files you wish to remotely access in the data folder. It is currently populated with sample files and folders.
3. Launch homely with launcher.py. Exiting the launcher will turn off dynamic file access, so any changes to files locally will not be reflected on the server until the launcher is restarted.
4. Bring the server offline with the "-s" option. You will be unable to access the site until it is launched again.

---

## Manual compilation

*This set-up is only recommended for advanced users.*

The installer only uses non-experimental standard library features and does not have any external dependencies. Compilation should work under most C++ standards.

1. Clone the repository.
2. Open the solution file with Visual Studio.
3. Build the solution and compile.
4. Run the executable.

---

Created and maintained by [flyyee](https://github.com/flyyee) under GNU General Public License v3.0