# Orange Updater - Quick Start Guide

## Installation Steps

### 1. Install Dependencies

Choose your distribution:

**Ubuntu/Debian:**
```bash
sudo apt update
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

### 2. Build the Application

```bash
cd OrangeUpdater
make
```

### 3. Run

```bash
./orange-updater
```

Or install system-wide:
```bash
sudo make install
orange-updater
```

## Basic Operations

### Update Package Lists
1. Select your package manager from the sidebar
2. Click "Update" button
3. Wait for completion

### Upgrade All Packages
1. Select package manager
2. Click "Upgrade" button
3. Enter sudo password when prompted

### Search for Packages
1. Select package manager
2. Enter package name in search box
3. Click "Search" button

### List Installed Packages
1. Select package manager
2. Click "List Packages" button

## Tips

- Use the **Refresh** button if package managers aren't detected
- All operations show real-time output
- Multiple package managers can coexist - manage them separately
- Sudo password may be required for system operations

## Common Issues

**"Package manager not detected"**
- Ensure the package manager is installed
- Click the Refresh button

**"Command failed"**
- Check if you have sudo permissions
- View the error message in the output area

**Build errors**
- Verify GTK3 development libraries are installed
- Check: `pkg-config --modversion gtk+-3.0`

## Need Help?

Check the full README.md for detailed documentation.
