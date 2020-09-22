# space_game_one
A real-time space trading game, written in C++, that looks like the classic TREK game from mainframes of old.

OVERVIEW

    This is a real-time text-based space trading game that visually looks
    like old mainframe TREK games, but instead of exploring the galaxy and 
    fighting klingons, you are a space trader trying to retire early by 
    making a profit as quickly as possible.

    I wrote this game in C++ using basic standard input and output streams
    and also the conio library for console functionality. This game is 
    composed of 18 files (8 .cpp files and 8 .h header files).

SUMMARY OF REQUIREMENTS

    Fly around in a spaceship to various space stations to buy and sell goods 
    for profit and to refuel.  Build wealth to purchase bigger ships.  Be 
    careful not to run out of fuel.

TIME

    Real-time will be used (the player has no control over time), but will be 
    scaled where 1 min = 1 hour game time.

FRAME RATE

    50 fps will be used, requiring a loop that blocks for 20ms.

PLAYING FIELD

    A (partial) inner-planetary system, radius = 150,000,000 km (in all 
    directions x,y,z), roughly 1 AU.

PORTS

    10 space stations will be randomly placed within the playing field.

    Names of each station:

        Arapahoe
        Berthoud
        Centennial
        Durango
        Eldora
        Fowler
        Gunnison
        Hooper
        Idalia
        Julesburg

MARKETS

    3 tradeable goods will be available with the following base prices and price
    fluctuations per hour (game time):

        organics        73          +/- 1
        computers       186         +/- 2
        robots          497         +/- 3
        
        Cap price fluctuations at 09% of the base price (+/-).

SHIPS
    
    Five levels of spacecraft will be available with the following 
    characteristics:

      CLASS        ENGINE (km/s)     CARGO   FUEL/HOUR    FUEL MAX
        1        38,973 (13% SOL)     23        2            14
        2        32,977 (11% SOL)     46        3            24
        3        26,981 (09% SOL)     92        4            40
        4        20,985 (07% SOL)     184       5            69
        5        14,990 (05% SOL)     368       6            117

IN FLIGHT COMMANDS 

    All commands can be used alone, and if an extended command is needed, the 
    player will be prompted. 

        help
        target
        dock
        map
        status
        save
        market
        sell
        buy
        exit

THE HELP COMMAND

    Type full-word commands at the command prompt and hit <enter>.  The 
    following commands are available:

        help            (this menu)
        target          (list all available places to go)
        dock            (attempt to dock with target object)
        map             (overhead map of system)
        status          (ship and player statistics)
        save            (save game)
        market          (list all markets and current prices)
        sell            (attempt to sell an item)
        buy             (attempt to buy an item)
        exit            (exit to main menu)

THE TARGET COMMAND
 
    The command ‘target’ used alone will bring up a list of stations, in 
    order of proximity (closest first).  Use ‘target b’ to select a 
    specific station (Berthoud).

    SELECT  STATION NAME    PROXIMITY (km)      ETA (hrs)   FUEL
    D       Durango         345,567             0.2         6
    E       Eldora          691,134             0.4         8
    A       Arapahoe        1,382,268           0.9         12
    J       Julesburg       2,764,536           1.7         14
    B       Berthoud        5,529,072           3.4         14
    I       Idalia          11,058,144          6.8         15
    F       Fowler          22,116,288          13.7        21
    G       Gunnison        44,232,576          27.3        32
    C       Centennial      88,465,152          54.6        44
    H       Hooper          176,930,304         28.6        46

THE DOCK COMMAND

    If the current target is within autopilot range and it is a stationary 
    target, the ship will dock.  To undock, select another target.

THE MAP COMMAND

    A ‘map’ command will be available to present a textual-based map to the 
    player in order to get a general sense of the playing field and spaceport 
    locations.

        . . . . . . . . . . . . . . . . . . . .
        . . A . . . . . . . . . . . . . . . . .
        . . . . . D . . . . . . . . . . . . . .
        . . . . . . . . . . . . . . . . . . C .
        . . . . . . . . . . . . . . . . . . . .
        . . . . . . . . . . . . . . . . . . . .
        . . . . . . . . . . . . . . . . . . . .
        . . . . . . . H . . . . . . . . . . . .
        . . . . . . . . . . . . . . . . . . . .
        . . . . . . . . . . . . . . . . . . . .
        . . . . . . . B . . . . . . . . . . . .
        . . . I . . . . . . . . . . . . . x . .
        . . . . . . . . . . F . . . . . . . . .
        . . . . . . . . . . . . . . . . . . . .
        . . . . . . . . . . . . . . . . . . . .
        . . . E . . . . . . . . . . . . . . . .
        . . G . . . . . . . . . . o . . . . . .
        . . . . . J . . . . . . . . . . . . . .

THE STATUS COMMAND
    
    Autopilot:  enroute to Berthoud Station [max velocity]
    Fuel:       27 units (33%)
    Velocity:   32,977 km/s (100%)
    Target:     Berthoud Station [34,127,445 km, ETA 0.2 hrs (12 min)]
    Cargo:      43 (22%) [ORG: 13, COM: 17, ROB: 13]
    Account:    $132,342

THE SAVE COMMAND

    Game saved.

THE MARKET COMMAND

    This will give an overview of the current market at all stations across the
    system:

        STATION       ORGANICS        COMPUTERS       ROBOTS
           A            +3               -2            +17
           B             0               +1            -5
           C            -2               +8            +9
           D            -43              +3            +24
           E            +4                0             0
           F             0               +1            -1
           G            +3               -2            +17
           H            -2               +8            +9
           I            +4                0             0
           J            +3               -2            +17

THE BUY/SELL COMMANDS

    ‘buy’ would prompt ‘buy fuel, organics, computers, or robots?’
   
    The user will type in the desired product and, if currently docked with a 
    station, the specified product will be brought on board (depending on 
    available space and player credits).

    The cargo hold will be filled to capacity with the specified product (or 
    until player credits are exhausted). The ‘sell’ command will work similarly.

THE EXIT COMMAND

    Will bring the player back to the main menu.

USER PATH
 
    Title Screen -> Introduction -> Main Menu
    Main Menu (New Game) -> Create new objects -> Game Loop
    Main Menu (Load Game) -> Load all objects -> Game Loop
    Main Menu (Exit) -> Exit
    Game Loop (Out of Fuel) -> Main Menu
    Game Loop (Exit) -> Main Menu
 
TITLE SCREEN

    ‘SPACE GAME I’ will display.

INTRODUCTION
 
    ‘Welcome to a day in the life of a Space Trader.  You are making a living by
    trading goods at various space stations around the solar system. He who dies
    with the most toys wins.  Just be careful not to run out of fuel...’

MAIN MENU

    1.  New Game
    2.  Load Saved Game
    3.  Exit

GAME LOOP
 
    The main game will loop every 20ms, accepting and responding to user input as 
    well as updating the objects in the game and the state of the game.  All
    commands are available here.
