ENCE260 Group Assignment
Group ID: 210
Authors: Paul Jackways (pja117), Katelyn McCarthy Freeman (kmc313)
Game: Totem terror

Set-up: There are various macro options for the game. These include the totem number of lives (MAX_HEALTH), total number of totems (TOTEM) (both from game.c0), the time an attack goes for (ATTACK_TIME), pacer frequency (PACER_FREQ) (attack.c). Make sure that if you are playing on two different computers, that these macros are the same for each device.

Plug the two UC funkits into the computer containing the gamefile. Open the the game in VSCode and type make into the terminal. You should see text start to appear in the terminal. After the terminal stops, type make program and wait for the text in the terminal to stop before typing make program again. You should see that both UC funkits have now turned on.

How to play:
Once make program is run on one of the funkits, a symbol will show with an arrow pointing down to a button. This indicates that the game is ready to play on that device. 
Place the two devices next to each other such that IR receiver matches up with IR transmitter. 

Arrows called 'totems' appear on the device. Your goal is to use the navswitch to select the correct totem. The '+' totem indicates that the navswitch should be pushed down. 
After each correct totem selection, the blue light will increase in brightness. This shows how close you are to attacking.
If you make an incorrect seleciton, you will be sent back to the start and the light will reset.

Once you have selected enough totems in a row correctly, the blue light will flash, indicating you are in attack mode. A random attack will be displayed, but you can change the attack by using the left and right buttons of the navswitch. 
The attacks are:
nuke - A nuclear explosion
lightning - a lightning strike
sword - cut the other person in half
bambooz - confuse and hypnotise the other player

to send your attack, use the button next to the IR receiver. This will disable the other player for a specified amount of time, and decrease their health bar.
Once a player's healthbar reaches zero, they are dead and the game will end on their device. The last player with their game still running is the winner.


