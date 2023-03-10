DevLog                               
THUS FAR: ~23:00h

//TODO:
- properly reset game state on game over
- change how player death is handled (short invulnerability and dont move back to center of screen)
- xp orb pickup visual polish with easings (20MTD inspired)

10/03
- //added XP orbs functionality
- //moved over from upgrading between waves to upgrading when enough xp
- //required xp scales with each lvl
- //background parallax
- //made grid slightly transparent


09/03
- //setup web builds and moved project over to MiniAsteroids repo

08/03
- //upgrades system 
- //balancing
- //bullets use lifetime
- //asteroids chase player

07/03 
- //basic wave control
- //asteroid spawn to work with waves
- //handle dead asteroids and bullets better
- //basic upgrade screen state added

06/03
- //replace cursor with cursor sprite
- //dont start updating gameplay screen until after fade is done
- //pause functionality to gameplay screen
- //add Camera2D
- //screen shake effect
- //trigger screen shake on player death + timer

03/03
- //make fade global, not screen dependant
- //add fade to other screen transitions

02/03
- //update struct Explosion to use struct AnimData
- //extract handling of updating anims into function
- //fix engine sprite/anim not wrapping around screen bounds
- //split up entities.h/.cpp - MORE TO IMPROVE
- //update main menu and game over screens 
- - //on press play bounce title up and press play text down
- - //fade in from center the game map and entities, when done start game
- - //game over to be defined
- //SetupGameMap based off of screen center, not window origin (top left)

01/03
- //refactor explosion anim struct to work for other anims
- //add bullet anim
- //add ship engine anim
- //use fire rate on mosue hold, not spam left click
- //refactor fire rate into bullet class - works but kind stupid
- //add window icon
- //dont spawn asteroids around player

28/02
- //setup new screen size - 1024x758
- //Read textures from the atlas
- //setup new playing area in 14x14 grid, cell size 8px(sprite size) * 6 scale_multi
- //setup grid to use sprite
- //setup entity wrapping to work only in grid not screen bounds
- //setup new UI with sprites out of playing area
- //replace ship and asteroids with sprites
- //fix ghost bullets
- //replace bullet with sprites
- //add explosion anim
- //add explosion sprite
