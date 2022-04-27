# Edutrail 2.1.6 (Current version)
*Quick fix*

## Patch Notes
- Fixed bug that crashed the program if a non-existent team or checkpoint was selected in quick registration mode.

## Known bugs with current release
- No known bugs

# Previous Versions


## Edutrail 2.1.5
*Quick fix*

#### Patch Notes
- Removed save option from "Save Management" submenu. Saving now occures automaticly when exiting the program or loading/creating another rebus. 
- Main menu now displays the eduTrail logo.

#### Known bugs
- No known bugs


## Edutrail 2.0.4
*Various bug fixes.*

#### Known bugs
* Selecting the save option from the settings submenu results in the program instantly crashing.

#### Compatibility issues
* no compatibility issues


## Edutrail 2.0.2
*Major overhaul of the entire source code.*

#### Known bugs
* Points can be registered without there being any teams to register them too. This would "trap" the user in the point registration menu.
* The user could easily break the program by entering a non-integer in quick mode point registration.
* If the program was unsuccessful in finding the save file it loops "Next Index: -1" indefinetly instead of showing an error message.
* Creating a new rebus would promt the user to select an existing rebus first.
* Menu options wrongly display "Edit/Remove Team" even tho removing teams is no longer a feature in this version of the program.

#### Compatibility issues
* no compatibility issues

## Edutrail 1.0.2
*Quick fix disabeling the very broken file system before user testing.*

#### Known bugs
* Settings menu does't do anything.
* Newly registerd points are pushed to the end of the points vector instead of being assigned to their specific checkpoint. This would result in a number of issues with displaying, changing and saving points.

#### Compatibility issues
* no compatibility issues

## Edutrail 1.0.1
*Minimum Viable Product*

#### Known bugs
* If a team does not have any points on a specific checkpoint, it would be saved as a blank space. This will cause the loading system to ignore the nonexistent value and instead add next value to that index instead, and thus misaligning the points vector with the checkpoints.
* After doing any operation in a submenu, you would be involuntarily returned to the main menu.
* The file system would leave an additional empty newline at the end of the file, resulting in the program being unable to read from the file.
* New checkpoints are not assigned a number or a gamemode value at their creation, resulting in extremely large random values being written in the save file, witch would crash the program the next time it was loaded.
* Newly registerd points are pushed to the end of the points vector instead of being assigned to their specific checkpoint. This would result in a number of issues with displaying, changing and saving points. This makes the amount of points larger then what the program expects, causing misalignement with the file pointer that eventually crashes the program.

#### Compatibility issues
* Users who did not have the standard c++ liberaries installed could not run the program.
  



