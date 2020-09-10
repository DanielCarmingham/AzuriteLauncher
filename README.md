# AzuriteLauncher

This was created out of frustration with not being able to debug Azure Functions using Azurite for the local Azure storage emulator because of this issue:
https://github.com/Azure/azure-functions-core-tools/issues/1247

This project outputs a binary named `AzureStorageEmulator.exe` that simply starts azurite.

Run this before debugging your Azure function and it fools the Azure SDK into thinking you already have the legacy Azure Storage Emulator running so it won't try to start it again (and fail).

### Prerequisites

*You must have Azurite installed via `npm i -g azurite` for this to work.*

More info about Azurite can be found at their project page: https://github.com/Azure/Azurite

## Easily run via PowerShell function

To make it even easier to start from PowerShell, you can create a function in your profile like this:

`Function startazurite {C:\___path_to_this_project___\Debug\AzureStorageEmulator.exe}`

Then you can start it by simply typing `startazurite` in PowerShell.

*Edit your profile easily with `notepad $Profile` from PowerShell prompt (or `code $Profile` if you have VS Code installed)*
