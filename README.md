# 🍊 Orange Updater

**A Universal Package Manager GUI for Linux**

Orange Updater is a graphical user interface application that provides a unified interface to manage all types of package managers installed on your Linux system. No more switching between terminal commands for different package managers!

![Version](https://img.shields.io/badge/version-1.0.0-orange)
![License](https://img.shields.io/badge/license-MIT-blue)

## ✨ Features

- **Multi-Package Manager Support**: Automatically detects and supports:
  - APT (Debian, Ubuntu, Linux Mint)
  - DNF (Fedora, RHEL 8+)
  - YUM (RHEL, CentOS)
  - Pacman (Arch Linux, Manjaro)
  - Flatpak
  - Snap
  - Zypper (openSUSE)

- **Unified Interface**: Manage all package managers from a single window
- **Common Operations**:
  - Update package lists
  - Upgrade all packages
  - List installed packages
  - Search for packages
  - Install/Remove packages
  - View package information
  - Rollback versions (where supported)

- **User-Friendly GUI**: Built with GTK3 for a modern, native Linux experience
- **Real-time Output**: See command output as operations execute
- **No Terminal Required**: All operations handled through the GUI

## 📋 Prerequisites

Before building Orange Updater, ensure you have:

- **GCC** compiler
- **GTK3** development libraries
- **pkg-config**
- **make**

### Install Dependencies

**Debian/Ubuntu:**
```bash
sudo apt install build-essential libgtk-3-dev pkg-config
```

**Fedora:**
```bash
sudo dnf install gcc gtk3-devel pkg-config make
```

**Arch Linux:**
```bash
sudo pacman -S base-devel gtk3 pkg-config
```

**openSUSE:**
```bash
sudo zypper install gcc gtk3-devel pkg-config make
```

## 🔧 Building from Source

1. **Clone or navigate to the project directory:**
```bash
cd OrangeUpdater
```

2. **Build the application:**
```bash
make
```

3. **Run the application:**
```bash
./orange-updater
```

## 📦 Installation

To install Orange Updater system-wide:

```bash
sudo make install
```

This will install:
- Binary to `/usr/local/bin/orange-updater`
- Scripts to `/usr/local/share/orange-updater/scripts/`

After installation, you can run it from anywhere:
```bash
orange-updater
```

## 🗑️ Uninstallation

To remove Orange Updater:

```bash
sudo make uninstall
```

## 🎮 Usage

1. **Launch the application:**
   ```bash
   ./orange-updater
   ```

2. **Select a package manager** from the left sidebar. Orange Updater will automatically detect which package managers are available on your system.

3. **Choose an operation:**
   - **Update**: Refreshes the package database
   - **Upgrade**: Updates all installed packages
   - **List Packages**: Shows all installed packages
   - **Search**: Find packages by name (enter search term and click Search)

4. **View output** in the main text area. All command output is displayed in real-time.

5. **Use the Refresh button** in the header to re-detect package managers.

## 🏗️ Project Structure

```
OrangeUpdater/
├── src/
│   ├── main.c              # Main application and GUI setup
│   └── operations.c        # Package manager operations
├── include/
│   └── orange_updater.h    # Header file with declarations
├── scripts/
│   ├── detect_managers.sh  # Detection script
│   ├── apt_operations.sh   # APT operations
│   ├── dnf_operations.sh   # DNF operations
│   ├── yum_operations.sh   # YUM operations
│   ├── pacman_operations.sh # Pacman operations
│   ├── flatpak_operations.sh # Flatpak operations
│   ├── snap_operations.sh  # Snap operations
│   └── zypper_operations.sh # Zypper operations
├── resources/              # Future: icons, desktop files
├── Makefile               # Build configuration
└── README.md             # This file
```

## 🔒 Permissions

Orange Updater requires sudo/root permissions for certain operations:
- Installing packages
- Removing packages
- Updating system packages
- Upgrading system packages

You'll be prompted for your password when executing these operations.

## 🐛 Troubleshooting

### Application won't build
- Ensure all dependencies are installed
- Check that GTK3 development files are present: `pkg-config --modversion gtk+-3.0`

### Package manager not detected
- Verify the package manager is installed: `which apt` (or `dnf`, `pacman`, etc.)
- Click the Refresh button in the application header
- Check script permissions: `ls -la scripts/`

### Commands fail
- Ensure you have the necessary permissions (sudo)
- Check if the package manager is properly configured
- View the output in the application for specific error messages

### Scripts not executable
The application automatically makes scripts executable, but if needed:
```bash
chmod +x scripts/*.sh
```

## 🚀 Future Enhancements

- [ ] Desktop file and system menu integration
- [ ] Package installation/removal through GUI
- [ ] Advanced filtering and sorting
- [ ] Update notifications
- [ ] Package version history
- [ ] Configuration file support
- [ ] Multi-language support
- [ ] Package dependency viewer
- [ ] Scheduled updates

## 🤝 Contributing

Contributions are welcome! Areas for improvement:
- Additional package manager support
- UI/UX enhancements
- Performance optimizations
- Bug fixes and testing

## 📄 License

This project is open source and available under the MIT License.

## 👤 Author

Built with ❤️ for the Linux community

## 🙏 Acknowledgments

- GTK Team for the excellent GUI toolkit
- Linux package manager maintainers
- Open source community

---

**Note**: Always back up your system before performing system-wide package operations. Orange Updater is provided as-is without warranty.
