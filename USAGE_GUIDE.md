# 🍊 Orange Updater - Complete Usage Guide

## Table of Contents
1. [Getting Started](#getting-started)
2. [Interface Overview](#interface-overview)
3. [Operations Guide](#operations-guide)
4. [Package Manager Specific Notes](#package-manager-specific-notes)
5. [Tips & Tricks](#tips--tricks)
6. [Troubleshooting](#troubleshooting)

---

## Getting Started

### First Launch

1. **Build and run:**
   ```bash
   cd OrangeUpdater
   ./build.sh
   ./orange-updater
   ```

2. **What you'll see:**
   - Main window with Orange Updater title
   - Left sidebar showing detected package managers
   - Toolbar with action buttons
   - Large output area showing welcome message
   - Status bar at bottom

### Your First Operation

1. Click on a package manager in the left sidebar (e.g., "apt" or "dnf")
2. Click the **"List Packages"** button to see installed packages
3. Wait for the output to appear in the main area

---

## Interface Overview

```
┌─────────────────────────────────────────────────────────────┐
│  Orange Updater                              [Refresh] [X]   │
├─────────────────────────────────────────────────────────────┤
│  [Update] [Upgrade] [List Packages] │ [Search Box] [Search] │
├───────────────┬─────────────────────────────────────────────┤
│ Package Mgrs  │                                             │
│ ┌───────────┐ │  Output Area                                │
│ │ apt       │ │  ────────────                                │
│ │ dnf       │ │                                             │
│ │ flatpak   │ │  Command output appears here                │
│ │ snap      │ │                                             │
│ └───────────┘ │                                             │
│               │                                             │
├───────────────┴─────────────────────────────────────────────┤
│  Status: Ready                                              │
└─────────────────────────────────────────────────────────────┘
```

### Components

**Header Bar:**
- Title and subtitle
- Refresh button (re-detect package managers)
- Close button

**Toolbar:**
- **Update Button**: Refresh package database
- **Upgrade Button**: Update all packages
- **List Packages Button**: Show installed packages
- **Search Box**: Enter package names
- **Search Button**: Search for packages

**Sidebar:**
- Lists all detected package managers
- Click to select active manager
- Selected manager highlighted

**Output Area:**
- Shows command execution results
- Real-time output display
- Scrollable for long outputs
- Monospace font for readability

**Status Bar:**
- Shows current status
- Displays selected package manager

---

## Operations Guide

### Update Package Database

**Purpose:** Refreshes the list of available packages

**Steps:**
1. Select a package manager
2. Click **"Update"**
3. Wait for completion

**What it does:**
- APT: `apt update`
- DNF: `dnf check-update`
- Pacman: `pacman -Sy`
- Flatpak: `flatpak update --appstream`

**Expected Output:**
- List of repositories being checked
- Number of packages that can be upgraded
- Success/failure message

---

### Upgrade All Packages

**Purpose:** Updates all installed packages to latest versions

**Steps:**
1. Select a package manager
2. Click **"Upgrade"**
3. Enter sudo password when prompted
4. Wait for completion (may take several minutes)

**⚠️ Warning:** This will update ALL packages. Large updates may download hundreds of MB.

**What it does:**
- APT: `apt upgrade -y`
- DNF: `dnf upgrade -y`
- Pacman: `pacman -Syu --noconfirm`
- Flatpak: `flatpak update -y`

**Expected Output:**
- List of packages being upgraded
- Download progress
- Installation progress
- Success/failure message

---

### List Installed Packages

**Purpose:** View all currently installed packages

**Steps:**
1. Select a package manager
2. Click **"List Packages"**
3. Browse the output

**What it does:**
- Shows package name and version
- May show description and size
- Output format varies by manager

**Tips:**
- Output can be very long (hundreds/thousands of packages)
- Use Ctrl+F to search within the output
- Scroll through the list

---

### Search for Packages

**Purpose:** Find specific packages by name or keyword

**Steps:**
1. Select a package manager
2. Type package name in search box (e.g., "firefox", "vim", "python")
3. Click **"Search"**
4. Review matching packages

**What it does:**
- Searches both installed and available packages
- Shows package descriptions
- May show additional package information

**Examples:**
- Search "browser" - finds web browsers
- Search "python" - finds Python-related packages
- Search "text editor" - finds text editing tools

---

## Package Manager Specific Notes

### APT (Debian/Ubuntu)
- **Best for:** Debian-based distributions
- **Speed:** Fast
- **Notes:** Most common on Ubuntu
- **Rollback:** Requires specific version number

### DNF (Fedora)
- **Best for:** Fedora, RHEL 8+
- **Speed:** Moderate
- **Notes:** Modern replacement for YUM
- **Rollback:** `dnf list --showduplicates`

### YUM (CentOS/RHEL 7)
- **Best for:** Older RHEL/CentOS
- **Speed:** Moderate
- **Notes:** Older than DNF
- **Rollback:** Limited support

### Pacman (Arch Linux)
- **Best for:** Arch-based distributions
- **Speed:** Very fast
- **Notes:** Rolling release model
- **Rollback:** Check package cache

### Flatpak
- **Best for:** Sandboxed applications
- **Speed:** Moderate
- **Notes:** Distribution-independent
- **Rollback:** Good support via commit history

### Snap
- **Best for:** Ubuntu applications
- **Speed:** Moderate
- **Notes:** Automatic updates by default
- **Rollback:** `snap revert` supported

### Zypper (openSUSE)
- **Best for:** openSUSE
- **Speed:** Moderate
- **Notes:** Powerful dependency resolver
- **Rollback:** Good version support

---

## Tips & Tricks

### Performance

1. **Update before upgrade:**
   - Always run Update before Upgrade
   - Ensures you have latest package information

2. **Use search before install:**
   - Search for packages to verify exact names
   - Some packages have different names on different systems

3. **Regular maintenance:**
   - Update once a week
   - Upgrade once a month (or as needed)

### Multiple Package Managers

- **Flatpak + System PM:** Common setup
  - Use system PM (apt/dnf) for system packages
  - Use Flatpak for GUI applications
  
- **Snap + APT on Ubuntu:**
  - APT for traditional packages
  - Snap for newer applications

### Safety

1. **Before major upgrades:**
   - Backup important data
   - Read the list of packages being updated
   - Check for kernel updates

2. **If something goes wrong:**
   - Check the output for error messages
   - Google the error message
   - Use rollback if available

### Efficiency

- **Keep the app open:** No need to close between operations
- **Use Refresh sparingly:** Only needed after installing new package managers
- **Search is your friend:** Faster than browsing through lists

---

## Troubleshooting

### Problem: No Package Managers Detected

**Solutions:**
1. Click the Refresh button in header
2. Verify package manager is installed: `which apt`
3. Check if scripts are executable: `ls -l scripts/`
4. Run detection script manually: `./scripts/detect_managers.sh`

---

### Problem: Command Fails with Permission Error

**Solutions:**
1. Ensure you're in the sudoers file
2. Try running from terminal: `sudo ./orange-updater`
3. Check sudo timeout: `sudo -v`

---

### Problem: Output Shows "Command Failed"

**Possible Causes:**
- Network connection issues (can't reach repositories)
- Package conflicts
- Disk space full
- Repository configuration errors

**Solutions:**
1. Check internet connection
2. Read error message in output
3. Try running the command manually in terminal
4. Check system logs: `journalctl -xe`

---

### Problem: Application Won't Start

**Solutions:**
1. Check if it compiled: `ls -l orange-updater`
2. Rebuild: `make clean && make`
3. Check dependencies: `pkg-config --modversion gtk+-3.0`
4. Run from terminal to see errors: `./orange-updater`

---

### Problem: Search Returns No Results

**Solutions:**
1. Check spelling of package name
2. Try partial names (e.g., "fire" instead of "firefox")
3. Package might not be available for your distribution
4. Update package database first

---

### Problem: Output Text is Unreadable

**Solutions:**
1. Maximize the window for more space
2. Use scroll bars to navigate
3. Copy output to text editor: Select text → Ctrl+C
4. Adjust terminal font size in code if needed

---

## Advanced Usage

### Running from Terminal

```bash
# Normal run
./orange-updater

# With debug output
./orange-updater 2>&1 | tee orange-updater.log

# As root (not recommended unless necessary)
sudo ./orange-updater
```

### Checking Script Output

```bash
# Test detection
./scripts/detect_managers.sh

# Test APT operations
./scripts/apt_operations.sh list

# Test search
./scripts/apt_operations.sh search firefox
```

### Installation Verification

```bash
# Check if installed system-wide
which orange-updater

# Check installed files
ls -l /usr/local/share/orange-updater/

# Check version
orange-updater --version  # (not implemented yet)
```

---

## Keyboard Shortcuts

While in the application:
- **Ctrl+C**: Copy selected text from output
- **Ctrl+F**: Find in output (if text is selectable)
- **Alt+F4**: Close application
- **Ctrl+Scroll**: Zoom text (in some GTK themes)

---

## Best Practices

1. **Regular Updates:**
   - Weekly: Update package databases
   - Monthly: Full system upgrade
   - As needed: Individual package updates

2. **Before Major Changes:**
   - Backup your data
   - Read changelogs
   - Test in VM if possible

3. **System Maintenance:**
   - Remove unused packages regularly
   - Clear package cache periodically
   - Keep only necessary package managers

4. **Learning More:**
   - Read man pages: `man apt`, `man dnf`
   - Check package manager documentation
   - Join distribution forums

---

## Getting Help

### In-App Help
- Check output messages carefully
- Status bar shows current state
- Welcome message explains basics

### External Resources
- README.md - Full documentation
- QUICKSTART.md - Quick reference
- PROJECT_SUMMARY.md - Architecture details

### Community
- Distribution forums
- Linux package manager documentation
- GitHub issues (if repository exists)

---

## Reporting Issues

When reporting problems, include:
1. Your Linux distribution and version
2. Package managers detected
3. Operation you were trying to perform
4. Complete error message from output area
5. Output of `./scripts/detect_managers.sh`

---

**Happy Package Managing! 🍊**

For more information, see:
- [README.md](README.md) - Full documentation
- [QUICKSTART.md](QUICKSTART.md) - Quick start
- [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) - Technical details
