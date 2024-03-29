﻿/// @file main.cpp: ez tartalmazza a main() függvényt, ami vezérli a program működését



//#define TESZT ///< Ha tesztelni szeretnénk, akkor itt kell definiálni a TESZT makrót


#ifndef TESZT

#define ART
#include "control.hpp"
using std::cin;
using std::cout;
using std::endl;

#endif // !TESZT

#ifdef TESZT
#include "test.h"
#endif // TESZT



int main()  // NOLINT(bugprone-exception-escape)
{

    //setbuf(stdout, 0);

#ifdef TESZT

    if (test_main())
        std::cout << "._. MINDEN KUL ._. " << endl;
    else
        std::cout << "): SZALAMI KERULT A PALACSINTABA / ERROR :(" << endl;
#endif // TESZT

#ifndef TESZT

    
    vector<Ember*> emberek; ///< Az embereket dinamikusan tároljuk, a rájuk mutató pointereket egy vektorban.
    vector<Kozpont*> kozpontok; ///< A központokat is dinamikusan tároljuk, a rájuk mutató pointereket egy vektorban.


    cout << R"(
                \||/
                |  @___oo
      /\  /\   / (__,,,,|		 / \----------------------, 
     ) /^\) ^\/ _)			 \_,|                     | 
     )   /^\/   _)			    |    Telefonkozpont   | 
     )   _ /  / _)			    |  ,--------------------
 /\  )/\/ ||  | )_)			    \_/___________________/ 
<  >      |(,,) )__)
 ||      /    \)___)\
 | \____(      )___) )___
  \______(_______;;; __;;;

)";

    cout << "\nA valasztott akcio sorszamat irja be alabb, hogy vegrehajthassa!\n\n";
    bool exit = false;

    while (true) {
        int choice = 0;
        cout <<
            R"(
    1)	Uj kozpont letrehozasa
    2)	Uj elofizeto letrehozasa
    3)	Hivas - uj kapcsolat letrehozasa / kapcsolat megszuntetese / uzenet kuldes a kapcsolaton keresztul
    4)	Elofizetoi bejelentkezes - uzenetek lekerdezese / torlese
    5)	Adott kozpont kapcsolatainak lekerdezese
    6)	Adatok importalasa *.txt file-bol
    7)	Adatok exportalasa
    8)  Kilepes

)" << endl;

        cin >> choice;
        if (cin.eof() || cin.bad() || cin.fail())
        {
            cout << "	Kilepett a programbol, viszont latasra!" << endl;
            break;
        }
        try {

            switch (choice) {

            case 1:
                try {
                    addnkp(&kozpontok);
                    cout << "\n	Sikeresen hozzaadott egy uj kozpontot az adatbazishoz." << endl;
                }
                catch (const char* exc) {
                    cerror(exc);
                    cout << "\n	Nem sikerult uj kozpontot hozzaadni az adatbazishoz. probalja ujra kesobb!" << endl;
                }
                break;

            case 2:
                try {
                    addnmbr(&emberek, &kozpontok);
                    cout << "\n	Sikeresen hozzaadott egy uj elofizetot az adatbazishoz." << endl;
                }
                catch (const char* exc) {
                    cerror(exc);
                    cout << "\n	Nem sikerult uj elofizetot hozzaadni az adatbazishoz. probalja ujra kesobb!" << endl;
                }
                break;

            case 3:
                try {
                    maincall(&kozpontok, &emberek);
                }
                catch (const char* exc) {
                    cerror(exc);
                }
                break;

            case 4:
                try {
                    login(&emberek);
                }
                catch (const char* exc)
                {
                    cerror(exc);
                }
                break;

            case 5:
                try {
                    kozpinfo(&kozpontok);
                }
                catch (const char* exc) {
                    cerror(exc);
                }
                break;

            case 6:
                try {
                    dimport(&kozpontok, &emberek);
                }
                catch (const char* exc) {
                    cerror(exc);
                }
                break;

            case 7:
                try {
                    dexport(&kozpontok, &emberek);
                }
                catch (const char* exc) {
                    cerror(exc);
                }
                break;

            case 8:
                exit = true;
                break;
#ifdef ART



            case 9:
                cout << R"(		It' ART time!!

88888888888888888888888888888888888888888888888888888888888888888888888
88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ -  .'|   |.'|     |  _..88
88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_-  .'  |.;'   |   _.!-'|  88
88      | `-!._  |  `;!  ;. _______________ ,'| .-' |   _!.i'     |  88
88..__  |     |`-!._ | `.| |_______________||."'|  _!.;'   |     _|..88
88   |``"..__ |    |`";.| i|_|MMMMMMMMMMM|_|'| _!-|   |   _|..-|'    88
88   |      |``--..|_ | `;!|l|MMoMMMMoMMM|1|.'j   |_..!-'|     |     88
88   |      |    |   |`-,!_|_|MMMMP'YMMMM|_||.!-;'  |    |     |     88
88___|______|____!.,.!,.!,!|d|MMMo * loMM|p|,!,.!.,.!..__|_____|_____88
88      |     |    |  |  | |_|MMMMb,dMMMM|_|| |   |   |    |      |  88
88      |     |    |..!-;'i|r|MPYMoMMMMoM|r| |`-..|   |    |      |  88
88      |    _!.-j'  | _!,"|_|M<>MMMMoMMM|_||!._|  `i-!.._ |      |  88
88     _!.-'|    | _."|  !;|1|MbdMMoMMMMM|l|`.| `-._|    |``-.._  |  88
88..-i'     |  _.''|  !-| !|_|MMMoMMMMoMM|_|.|`-. | ``._ |     |``"..88
88   |      |.|    |.|  !| |u|MoMMMMoMMMM|n||`. |`!   | `".    |     88
88   |  _.-'  |  .'  |.' |/|_|MMMMoMMMMoM|_|! |`!  `,.|    |-._|     88
88  _!"'|     !.'|  .'| .'|[@]MMMMMMMMMMM[@] \|  `. | `._  |   `-._  88
88-'    |   .'   |.|  |/| /                 \|`.  |`!    |.|      |`-88
88      |_.'|   .' | .' |/                   \  \ |  `.  | `._    |  88
88     .'   | .'   |/|  /                     \ |`!   |`.|    `.  |  88
88  _.'     !'|   .' | /                       \|  `  |  `.    |`.|  88
88 vanishing point 8888888888888888888888888888888888888888888888888888

)" << endl;
                
                break;

            case 11:
                cout << R"(

 .===============================================================.
 |  ,-----------------,                                          |
 | /| HELP THE BUNNY  |==========.===.   .===.   .===========.   |
 || |    FIND HIS     |          |   |   |   |   |      .-.  | E |
 || |  EASTER EGGS!   |  |===|   |   |   |   |   |..==./xxx\ | N |
 || |_________________|          |   |       |   /<<<<<\    || D |
 ||/_________________/   .======='   |   .   |   \>>>>>/xxxx/--. |
 |   |   |           |   |           |   |   |   |`'==''---; * *`\
 |   |   '==========='   |   |======='   |   |   |   ,===. \* * */
 |   |                   |               |   |   |   |   |  '--'`|
 |   '===============|   '===.   |===.   |   |   |==='   '=======|
 |                           |       |   |   |   |               |
 |   |===============.   .   '===|   |   |===|   |   .=======.   |
 |                   |   |           |   |   |   |   |       |   |
 |   .===========.   |   |   |===.   |   |   |   |   |   |   |   |
 |   |           |   |   |       |   |   |   |   |   |   |   |   |
 |   |   .===.   |   |   |===.   '===|   |   '==='   |   |   |   |
 |   |   |   |   |   |   |   |       |   |           |   |   |   |
 |   '==='   /`\ '==='   |   '===.   |   '===========|   |   |   |
 |          / : |                |   |               |   |   |   |
 | _.._=====| '/ '===|   .======='   '===========.   |   |   |   |
 /`    \    | /          |                       |   |   |       |
|  .-._ '-"` (=======.   |   .===============.   |   |   '===.   |
|_/  |/   e  e\==.   |   |   |               |   |   |       |   |
 | S ||  >   @ )<|   |   |   |   .=======.   |   |   |===.   |   |
 | T | \  '--`/  |   |   |   |   |       |   |   |   |   |   |   |
 | A | / '--<`   |   |   |   |   |   |   |   |   '==='   |   '   |
 | R || ,    \\  |           |   |   |   |   |           |       |
 | T |; ;     \\__'======.   |   |   '==='   |   .===.   |   |   |
 |   / /      |.__)==,   |   |   |           |   |   |   |   |   |
 |  (_/,--.   ; //"""\\  |   |   '==========='   |   '==='   |   |
 |  { `|   \_/  ||___||  |   |                   |           |   |
 |   ;-\   / |  |(___)|  |   '===========.   |   '=======.   |   |
 |   |  | /  |  |XXXXX|  |               |   |           |   |   |
 |   | /  \  '-,\XXXXX/  |   .==========='   '=======.   |   |   |
 |   | \__|----' `"""`   |   |                       |   |   |   |
 |   '==================='   '======================='   '==='   |
 |                                                               |
 '==============================================================='
)" << endl;
                
                break;


            case 42:
                cout<<R"(		Say hello to David!

                                    **   **
                               **************  *****
                            **$$$$  ****   $$*******
                          * $$$$$$$$$   $$* **   *$**
                         *  $    $$$$$* $* *$$$$$$$$$**
                        *  $$$$$$$$$$$$$ $$$$$$$$$**$$*
                        $$  $$$$$$$ $$$$$$$$ $$$$$$$$$$$$
                      *$ *$$$$$$$$$$$*$*$*$    *****$***
                    **$$ $$$$$$*$ **    [[[[[[[   [[[
                    **$**$$**$$$@@     [  #####  ## #
                  *$$$*****$$$$$$         ..###   ###
                  **$$$$$$$$ [[$$ ##        +++   ###
                   $$$$$$**[[  [[$$    #          ##
                     $$$***#[  #     ###      #   ##
                     $$$$$$ ##++ #+        ## ######
                     $$$$$#  ###       ##       ##
                     $$$$$#   ##            ######
                       $$$### ##      ##    #####
                         $#$ #  +##  #   ##  ## #
                         $$$$     #   +++#######
                         $$*      ##############
                         *$$# #  ++     ++++        ######
                         $$###         ++###      ##      ++
                         $# +#      #######+     +##+   ## ##
                         *#+ ##     ++###+###    +  ###+     ##
                         ## ##+#  # ++ +++++##  +  #++##       ##
                        ##+#  ##  ++##+     ###++ ##++           #
                       ##+ +   ++  +##+  +   +######## #          #
                     ###+     ++++##          ++ # # ##+         ##
                 ####  +        ++            +++++# ## ##+        #
            ###++   +                           ##############+ +##+##
          ##+       ##                         ++#+ ++#########++##  "
        ####+                                    +#+ +++###############
      ###                                       ++++++#+++++##########
     ##+                                            ++ +     ####+++++
    ##                              ++               +++        ##  ++
    ##+                  ++                         +++++ +  # # ##+++
    #      ++  +           ++                       ++@++ ++##### # ++
    #    +   ####+                                +++++++###++####+##
    #    +   ####+                                +++++++###++####+##
    #   +    ###++                               +++++######## #######
    #  +++    ####++++@                          +++++++++###   ###  #
    #+ #+      ###++++++++                            ++++++#   ##+++#
    ##+ +      #### #####++++                          ++++##    ###++
    ##++      ###########++                          ++++++#      ## +
    ###+      ##########+++                             #++#        ##
    #+  +    +########++                         ++##########     
   ###+        # ###+++++                         +++++#####      
  ###+  +      #  ##+++                          +++++#######     
  ##++##+     ##   ##++  ##                       ###########     
   ##+##+     ###  ######              #####     ###++++#####
   ##  ##     ##      ##  ######  ++              #+  ######
   ##+#       ##      ##  ######+++++             ++ #######
  ### #+    ###       ##  ########                  ## ####
  ######+    ##       ##++    ##+                  ## ## ##
 +###  ####+##       ##                            +     #+
 ##++ +  ######      ##                                  ##
 +##       ++ #     +#                 @@@                #
 +#         + #    ##                                    ##
 ## +       # #    #                                      #+
 ##+        # #    # +                                    #+
 ##+        # #    ## ###                                ###
 ##+  +     ###    ##    ####                            +##
 #++     #  ##+   +#  ########                          ####
##++        ##    ## ++   ####                         #####
 ##++       ++    #         +##         ##            ######
+# +        +#   +#           +#+      #####         ######+
 # +       +#    #           +#+   ############           +##
 # +      ##    +#           +###+  ######### +###++      +#
  ##++  + #     #     #             ###   #  #######++     #
  ##++  + #     ##             +### #+#  #+####        #
  ##+    +##    ##     ##         +###++#   #++####        #
  # + +  +#     #                 +#+++# #+++###+         #
   #      #     # +++++           +#+++# #+++###++        ##
  +#      #     #    #####+        +#+++# #+++####++        #
  # ##    ###   ###++           ++##+++# #+++####          #
  ########  ##  ###              ###++## ##++##             #
    ### ##     ## ##                ###########               #
   ##+ ###      #####              #########                 #
    ##### ###     ##+               ## ## ###                 +
    ########## #  ##++             +++###++++                 +
    ########## #  #++              ++##### ++++                ++
    ++## ++  ++  ## #+               ++### #++++               +
      ########### ## #+            ++++##+++++++                +
        ##+++  #  #### ++           ++### #+++++++              ++
          #+####    ##++          +++##+ #####++ +             ++
           ##### + + ### ++++      ++###  #####++ +            ++
             ########### #++++    ++###  #####++ +             +
              +###+ ##### ++ ++ +   +#      +# #++  +            +
                    ##############  ##       +### ++            ++
                     ####+++++###+  ##         ## ++           +++
                     #####+++#####  ##          ##+#            ++
                     ########+###++  #           ###             +
                      ###### # ## #  #           ##++            +
                       ## ## ## ## ## #           # # ##         +
                       ####  #  ++ # ##           +#  #+         +
                       ## ++       # ##            #####         ++
                       ######  #   +###             ####+         +
                       # ####      ####             #####+         +
                        +#+ ## +#### ##               ####+++  +     #
                          ##  #  #######               ###### ###   ##
                         #    ##  #  ###                 ######+++   ##
                        #########  #####                 ######+++   #
                        ## # # ## # # #                   ## # #  
                         ##  # +  #  ##                    +## + + +
                        # ###   #     #                     # ### #
                        #  ###+++     #+                    ## ++  #
                        ## #####      ##                    ## ## ####
                        # ######       #                    ## # +  +
                        # + + +#       #                     # + + + +
                         # +  ##       #                     # + + + +
                          #+ ++##     ##                      # # #+ +
                           #+ + +     +#                      ### # +
                           # + + +      #                      +# + +
                           # + +  +     #                       ### ##
                            # ###++     ##                        ## #
                              #  #      ##                        ####
                               # #      #+                         ###
                                ## #   ###                          ##
                                 ## #   ##                          ##
                                  ### ## #
                                  +##  +##
                                   ##    #
                                   +#    #
                                   +#++   "
                                    ## +   #
                                    ##+     ##
                                    # #     +#
                                   #+      ###
                                    +# +    ++#
                                    ##   +   +#
                                   ## +     +##
                                  ###       #+#
                                 #+         + #
                               ##           +##
                               #+ # # # +#    #
                                ##+ #  # #   ##
                                 #+##+#  ####+
)" << endl;
                
                break;

            case 12:
                cout << R"(   Next trip?
                       ,-.^._                 _
                     .'      `-.            ,' ;
          /`-.  ,----'         `-.   _  ,-.,'  `
       _.'   `--'                 `-' '-'      ;
      :                         o             ;    __,-.
      ,'    o            Mazar-i-Sharif       ;_,-',.__'--.
     :    Herat                              ,--```    `--'
     :                                      ;
     :                                      :
     ;                                      :
    (                                       ;
     `-.                           *      ,'
       ;                         Kabul   :
     .'                             .-._,'
   .'                               `.
_.'                                .__;
`._                  o            ;
   `.             Kandahar       :    ,---------------------.
     `.               ,..__,---._;    |    AFGHANISTAN      |
       `-.__         :                | Capital: Kabul      |
            `.--.____;                | Pop: 12700000       |
                                      | Area: 250000 sq.mi. |
                                      |      (647500 sq.km.)|
                                      `---------------------'
)" << endl;
                
                break;
            case 13:
                cout << R"(     ___It's movie time___
           ....
         ,''. :   __
             \|_.'  `:       _.----._//_
            .'  .'.`'-._   .'  _/ -._ \)-.----O
           '._.'.'      '--''-'._   '--..--'-`
            .'.'___    /`'---'. / ,-'`
snd       _<__.-._))../ /'----'/.'_____:'.
   \_    :            \ ]              :  '.
     \___:             \\              :    '.
         :              \\__           :    .'
         :_______________|__]__________:  .'
                    .' __ '.           :.'
                  .' .'  '. '.
                .' .'      '. '.
              .' .'          '. '.
           _.' .'______________'. '._
          [_0______________________0_]

                . . .

                            /  \      __
.---.                  _   /   /   _.~  \
\    `.               / \ /   /.-~    __/
 `\    \              |  |   |/    .-~ __
   \    \             |  |   |   .'--~~  \
    \    \            |  |   `  ' _______/
     \    \           |  `        /
 .--. \    \          |    `     /
 \   `.\    \          \        /
  `\   \     \          `\     (
    \   \     \           > ,-.-.
     \   `.    \         /  |  \ \
      \    .    \       /___| O |O\     ,
   .-. \    ;    |    /`    `^-.\.-'`--'/
   \  `;         |   |                 /
    `\  \        |   `.     `--..____,'
      \  `.      |     `._     _.-'^
       \   .     /         `|`|`
     .-.\       /           | |
     \  `\     /            | |
      `\  `   |             | |
        \     |             | |
       .-.    |             | |
       \  `.   \            | |
        `\      \           | |
          \      \          | |
           \_____ :-'~~~~~'-' ;
           /____;``-.         :
          <____(     `.       ;
            \___\     ;     .'
               /``--'~___.-'
              /\___/^/__/
             /   /' /`/'
             \  \   `\ \
              `\ \    \ \
                \ \    \ \
                 \ \    \ \
                  \ \    \ \     ______
                   \ \ ___\ \'~``______)>
                    \ \___ _______ __)>
                _____\ \'~``______)>
              <(_______.._______)>
)" << endl;
                
                break;

            case 14:
                cout << R"(
                                       .:::::::::.
                                    .::::::::::::::::,       .::
                                  -'`;. ccccr -ccc,```'::,:::::::
                                     `,z$$$$$$c $$$F.::::::::::::
                                      'c`$'cc,?$$$$ :::::`:. ``':
                                      $$$`4$$$,$$$$ :::',   `
                                ..    F  .`$   $$"$L,`,d$c$
                               d$$$$$cc,,d$c,ccP'J$$$$,,`"$F
                               $$$$$$$$$$$$$$$$$$$$$$$$$",$F
                               $$$$$$$$$$$ ccc,,"?$$$$$$c$$F
                               `?$$$PFF",zd$P??$$$c?$$$$$$$F
                              .,cccc=,z$$$$$b$ c$$$ $$$$$$$
                           cd$$$F",c$$$$$$$$P'<$$$$ $$$$$$$
                           $$$$$$$c,"?????""  $$$$$ $$$$$$F
                       ::  $$$$L ""??"    .. d$$$$$ $$$$$P'..
                       ::: ?$$$$J$$cc,,,,,,c$$$$$$PJ$P".::::
                  .,,,. `:: $$$$$$$$$$$$$$$$$$$$$P".::::::'
        ,,ccc$$$$$$$$$P" `::`$$$$$$$$$$$$$$$$P".::::::::' c$c.
  .,cd$$PPFFF????????" .$$$$$b,
z$$$$$$$$$$$$$$$$$$$$bc.`'!>` -:.""?$$P".:::'``. `',<'` $$$$$$$$$c
$$$$$$$$$$$$$$$$$$$$$$$$$c,=$$ :::::  -`',;;!!!,,;!!>. J$$$$$$$$$$b,
?$$$$$$$$$$$$$$$$$$$$$$$$$$$cc,,,.` ."?$$$$$$$$$$$$$$$$$$.
     ""??"""   ;!!!.$$$ `?$$$$$$P'!!!!;     !!;.""?$$$$$$$$$$$$$$$r
               !!!'<$$$ :::..  .;!!!!!!;   !!!!!!!!!!!!!>  "?$$$$$$$$$$$"
              !!!!>`?$F::::::::`!!!!!!!!! ?"
                  `!!!!>`::::: :: 
               `    `!!! `:::: ,, ;!!!!!!!!!'`    ;!!!!!!!!!!!
                \;;;;!!!! :::: !!!!!!!!!!!       ;!!!!!!!!!!!!>
                `!!!!!!!!> ::: !!!!!!!!!!!      ;!!!!!!!!!!!!!!>
                 !!!!!!!!!!.` !!!!!!!!!!!!!;. ;!!!!!!!!!!!!!!!!>
                  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
                  `!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
                   `!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    `
                       ?$$c``!!! d $$c,c$.`!',d$$$P
                           `$$$$$c,,d$ 3$$$$$$cc$$$$$$F
                            `$$$$$$$$$b`$$$$$$$$$$$$$$
                             `$$$$$$$$$ ?$$$$$$$$$$$$$
                              `$$$$$$$$$ $$$$$$$$$$$$F
                               `$$$$$$$$,?$$$$$$$$$$$'
                                `$$$$$$$$ $$$$$$$$$$P
                                  ?$$$$$$b`$$$$$$$$$F
                                ,c$$$$$$$$c`$$"$$$$$$$cc,
                            ,z$$$$$$$$$$$$$ $L')$$$$$$$$$$b,,,,, ,
                       ,,-=P???$$$$$$$$$$PF $$$$$$$$$$$$$Lz =zr4%'
                      `?'d$ $b = $$$$$$           "???????$$$P
                         `"-"$$$$P""""                     "
)" << endl;
                
                break;
            case 44:
                cout << R"(
             ,----------------,              ,---------,
        ,-----------------------,          ,"        ,"|
      ,"                      ,"|        ,"        ,"  |
     +-----------------------+  |      ,"        ,"    |
     |  .-----------------.  |  |     +---------+      |
     |  |                 |  |  |     | -==----'|      |
     |  |  I LOVE DOS!    |  |  |     |         |      |
     |  |  Bad command or |  |  |/----|`---=    |      |
     |  |  C:\>_          |  |  |   ,/|==== ooo |      ;
     |  |                 |  |  |  // |(((( [33]|    ,"
     |  `-----------------'  |," .;'| |((((     |  ,"
     +-----------------------+  ;;  | |         |,"     
        /_)______________(_/  //'   | +---------+
   ___________________________/___  `,
  /  oooooooooooooooo  .o.  oooo /,   \,"-----------
 / ==ooooooooooooooo==.o.  ooo= //   ,`\--{)B     ,"
/_==__==========__==_ooo__ooo=_/'   /___________,"
`-----------------------------'
)" << endl;
                break;

#endif // ART

            default:
                exit = true;
                break;

            }
        }
        catch (...) {
            exit = true;
            cerror("Valami ismeretlen hiba tortent");
        }

        if (exit) {
            cout << R"(
 / \------------------------, 
 \_,|                       | 
    |    Viszont latasra!   | 
    |  ,----------------------
    \_/_____________________/ 
)" << endl;
            break;
        }
    }

    for (size_t i = 0; i < kozpontok.size();i++)
    {
        delete kozpontok[i];
    }
    for (size_t i = 0; i < emberek.size();i++)
    {
        delete emberek[i];
    }

    char c;
    cin >> c;


#endif // !TESZT
    return 0;
}
