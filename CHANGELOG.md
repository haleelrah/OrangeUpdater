# Changelog - Orange Updater

## Version 1.1.0 - December 27, 2025

### 🎉 New Features

#### Package Installation from Search Results
- **Install Button**: New button in toolbar to install packages
- **Auto-populate**: After searching, the package name is automatically filled in the package entry field
- **Quick Install**: Search for a package, then click Install to add it to your system
- **Visual Feedback**: Clear confirmation messages before installation

#### Package Removal
- **Remove Button**: Uninstall packages through the GUI
- **Safety**: Confirmation message before removal
- **sudo Support**: Automatically prompts for administrator privileges

#### Rollback/Version Management
- **Rollback Button**: New button to manage package versions
- **Package-Manager Specific**:
  - **Snap**: Actual rollback functionality - reverts to previous version automatically
  - **APT**: Shows available versions and instructions to install specific versions
  - **DNF**: Displays version history and downgrade commands
  - **Flatpak**: Shows commit history for version control
  - **YUM**: Lists available versions
  - **Pacman**: Shows package cache for rollback options
  - **Zypper**: Displays available versions
- **Formatted Output**: Clean, easy-to-read output with instructions

### 🐛 Bug Fixes

#### DNF Package Listing Fixed
- **Issue**: DNF and YUM were not displaying installed packages correctly
- **Cause**: Header line filtering was removing actual package data
- **Fix**: Changed from `grep -v` to `tail -n +2` to skip header line properly
- **Result**: DNF and YUM now properly list all installed packages

#### YUM Package Listing Fixed
- **Issue**: Same issue as DNF
- **Fix**: Applied same solution with `tail -n +2`
- **Result**: YUM package listing now works correctly

### 🎨 UI Improvements

#### Enhanced Toolbar
- **Reorganized Layout**:
  - Group 1: Update, Upgrade, List Packages
  - Group 2: Install, Remove, Rollback
  - Group 3: Package name entry field
  - Group 4: Search entry and button
- **Visual Separators**: Clear separation between button groups
- **Dual Input Fields**:
  - Search field for finding packages
  - Package field for install/remove/rollback operations

#### Better User Feedback
- **Status Bar Updates**: More informative messages after operations
- **Warning Messages**: Clear warnings before destructive operations
- **Success/Failure Indicators**: Visual indicators for operation results
- **Usage Hints**: Helpful tips when fields are empty

### 📝 Script Enhancements

#### Rollback Scripts Improved
All package manager rollback scripts now provide:
- Formatted output with clear headers and separators
- Current version information
- Available versions/commits
- Clear instructions for manual rollback
- Example commands for users to copy

#### Snap Rollback
- **Automated**: Actually performs the rollback automatically
- **Before/After**: Shows package info before and after revert
- **Error Handling**: Clear messages if no previous version exists

### 🔧 Technical Changes

#### Header File Updates
- Added new widget pointers: `install_btn`, `remove_btn`, `rollback_btn`, `package_entry`
- Added `last_searched_package` field to track searches
- Added function declarations for new callbacks

#### Main Application
- Toolbar reorganization with new buttons
- Dual entry fields for different purposes
- Proper signal connections for all new buttons
- Initialization of new tracking variables

#### Operations Module
- `on_install_clicked()`: New callback for package installation
- `on_remove_clicked()`: New callback for package removal
- `on_rollback_clicked()`: New callback for version management
- Enhanced `on_search_clicked()`: Now populates package entry field
- Better error messages and user guidance

### 📊 Statistics

**Code Changes**:
- Modified: 5 files (2 C, 3 bash scripts, 1 header)
- Added: ~150 lines of new code
- Enhanced: 4 rollback scripts
- Fixed: 2 package listing bugs

**New Functionality**:
- 3 new buttons
- 3 new callback functions
- 1 new entry field
- Enhanced rollback for 7 package managers

### 🚀 Usage Examples

#### Install a Package
1. Select package manager (e.g., flatpak)
2. Type package name in search box
3. Click "Search"
4. Review results
5. Click "Install" (package name auto-filled)
6. Enter sudo password when prompted

#### Remove a Package
1. Select package manager
2. Type package name in package field
3. Click "Remove"
4. Confirm with sudo password

#### Rollback a Package
1. Select package manager
2. Enter package name
3. Click "Rollback"
4. For Snap: Automatic revert
5. For others: Follow displayed instructions

### ⚠️ Breaking Changes
None - All existing functionality preserved

### 🔜 Future Improvements
- [ ] Package selection from list view
- [ ] Confirmation dialogs before destructive operations
- [ ] Package dependency viewer
- [ ] Batch operations (install/remove multiple packages)
- [ ] Package categories/filtering
- [ ] History of operations
- [ ] Scheduled updates

### 🐛 Known Issues
- DNF list command may be slow on systems with many packages
- Rollback requires manual command execution for most package managers (except Snap)
- No confirmation dialog before install/remove (uses terminal sudo prompt)

### 📚 Documentation Updates Needed
- [ ] Update README.md with new features
- [ ] Update USAGE_GUIDE.md with install/remove/rollback instructions
- [ ] Add screenshots showing new buttons
- [ ] Update QUICKSTART.md with new workflow

---

## Version 1.0.0 - December 27, 2025

### Initial Release
- GTK3 GUI interface
- Support for 7 package managers
- Update/Upgrade operations
- Package listing
- Package search
- Real-time command output
- Automatic package manager detection

---

**Note**: Always backup your system before performing major package operations.
