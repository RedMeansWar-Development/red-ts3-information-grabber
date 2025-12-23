# Red's TS3 Information Grabber (RTIG)
A TeamSpeak 3 plugin that provides detailed client, server, and channel information in an easy-to-read format.

## Features
- **Server Information Display**: Shows comprehensive server details including:
  - Server name and unique identifier
  - Platform and version information
  - Client statistics (online/max/reserved slots)
  - Channel count
  - Server uptime with human-readable format
  - Server creation date
  - Download/upload quotas
  - Security level requirements

- **Formatted Output**: Information is displayed with color-coded BB formatting for better readability

## Requirements
- TeamSpeak 3 Client
- Windows 64-bit / Linux / macOS (depending on your build)
- Visual C++ 2015-2022 Redistributable (Windows only)

## Installation

### Windows
1. Download the latest release from the [Releases](../../releases) page
2. Extract `rtig_win64.dll`
3. Copy the DLL to your TeamSpeak 3 plugins folder or run the TeamSpeak plugin installer:
   - Default location: `C:\Users\[YourUsername]\AppData\Roaming\TS3Client\plugins\`
4. Restart TeamSpeak 3
5. Go to `Settings > Plugins` and enable "RTIG"

### Linux
1. Download the latest release
2. Extract `rtig_linux.so`
3. Copy to: `~/.ts3client/plugins/`
4. Restart TeamSpeak 3 and enable the plugin

### macOS
1. Download the latest release
2. Extract `rtig_macos.dylib`
3. Copy to: `~/Library/Application Support/TeamSpeak 3/plugins/`
4. Restart TeamSpeak 3 and enable the plugin

## Usage

Once installed and enabled, the plugin will provide server information through TeamSpeak's interface. (Add specific usage instructions based on how your plugin exposes the information - e.g., command, menu item, etc.)

## Building from Source

### Prerequisites
- CMake 3.21 or higher
- C++20 compatible compiler (MSVC 2019+, GCC 10+, or Clang 11+)
- TeamSpeak 3 Plugin SDK

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/red_ts3_information_grabber.git
cd red_ts3_information_grabber

# Create build directory
mkdir build
cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

The compiled plugin will be in the `out/build/x64-release` directory.

## Project Structure

```
red-ts3-information-grabber/
├── include/
│   ├── red_ts3_info/
│   │   └── common.h
│   │   └── plugin.h
│   │   └── ts3_channel_info.h
│   │   └── ts3_client_info.h
│   │   └── ts3_server_info.h
│   └── ts3_sdk/              # TeamSpeak 3 SDK headers
├── src/
│   └── plugin.cpp
│   └── ts3_channel_info.cpp
│   └── ts3_client_info.cpp
│   └── ts3_server_info.cpp
├── CMakeLists.txt
└── LICENSE.md
└── README.md
```

## Information Displayed

The plugin displays the following server information:
- **Server Name**: The display name of the server
- **Server UID**: Unique identifier for the server
- **Platform/Version**: Server software version and operating system
- **Clients Online**: Current clients vs. max capacity (including reserved slots)
- **Channels**: Total number of channels on the server
- **Uptime**: How long the server has been running
- **Server Age**: When the server was first created
- **Download/Upload Quota**: Bandwidth limitations (if any)
- **Security Level**: Required identity security level to connect

## Development

### Code Style
- C++20 standard
- Use meaningful variable names
- Comment complex logic
- Follow existing code structure

### Contributing
Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Acknowledgments
- TeamSpeak Systems GmbH for the TeamSpeak 3 Plugin SDK

## Support
If you encounter any issues or have questions:
- Open an issue on [GitHub Issues](../../issues)

## Changelog

### Version 1.0.0
- Initial release
- Server information display
- Uptime and creation date formatting
- Multi-platform support (Windows/Linux/macOS)
---
