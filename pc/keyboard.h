#define BEL         7                                   /*  Bell            */
#define BS          8                                   /*  Backspace       */
#define TAB         9                                   /*  Tab             */
#define LF         10                                   /*  Linefeed        */
#define CR         13                                   /*  Return          */
#ifdef ESC
#undef ESC
#endif
#define ESC        27                                   /*  Escape          */
#define SPACE      32                                   /*  Space           */
#define CTRL_A      1                                   /*  CTRL + A        */
#define CTRL_B      2                                   /*  CTRL + B        */
#define CTRL_C      3                                   /*  CTRL + C        */
#define CTRL_D      4                                   /*  CTRL + D        */
#define CTRL_E      5                                   /*  CTRL + E        */
#define CTRL_F      6                                   /*  CTRL + F        */
#define CTRL_G      7                                   /*  CTRL + G        */
#define CTRL_H      8                                   /*  CTRL + H        */
#define CTRL_I      9                                   /*  CTRL + I        */
#define CTRL_J     10                                   /*  CTRL + J        */
#define CTRL_K     11                                   /*  CTRL + K        */
#define CTRL_L     12                                   /*  CTRL + L        */
#define CTRL_M     13                                   /*  CTRL + M        */
#define CTRL_N     14                                   /*  CTRL + N        */
#define CTRL_O     15                                   /*  CTRL + O        */
#define CTRL_P     16                                   /*  CTRL + P        */
#define CTRL_Q     17                                   /*  CTRL + Q        */
#define CTRL_R     18                                   /*  CTRL + R        */
#define CTRL_S     19                                   /*  CTRL + S        */
#define CTRL_T     20                                   /*  CTRL + T        */
#define CTRL_U     21                                   /*  CTRL + U        */
#define CTRL_V     22                                   /*  CTRL + V        */
#define CTRL_W     23                                   /*  CTRL + W        */
#define CTRL_X     24                                   /*  CTRL + X        */
#define CTRL_Y     25                                   /*  CTRL + Y        */
#define CTRL_Z     26                                   /*  CTRL + Z        */
#define BACKTAB   271                                   /*  TAB + SHIFT TAB */
#define ALT_Q     272                                   /*  ALT + Q         */
#define ALT_W     273                                   /*  ALT + W         */
#define ALT_E     274                                   /*  ALT + E         */
#define ALT_R     275                                   /*  ALT + R         */
#define ALT_T     276                                   /*  ALT + T         */
#define ALT_Y     277                                   /*  ALT + Y         */
#define ALT_U     278                                   /*  ALT + U         */
#define ALT_I     279                                   /*  ALT + I         */
#define ALT_O     280                                   /*  ALT + O         */
#define ALT_P     281                                   /*  ALT + P         */
#define ALT_A     286                                   /*  ALT + A         */
#define ALT_S     287                                   /*  ALT + S         */
#define ALT_D     288                                   /*  ALT + D         */
#define ALT_F     289                                   /*  ALT + F         */
#define ALT_G     290                                   /*  ALT + G         */
#define ALT_H     291                                   /*  ALT + H         */
#define ALT_J     292                                   /*  ALT + J         */
#define ALT_K     293                                   /*  ALT + K         */
#define ALT_L     294                                   /*  ALT + L         */
#define ALT_Z     300                                   /*  ALT + Z         */
#define ALT_X     301                                   /*  ALT + X         */
#define ALT_C     302                                   /*  ALT + C         */
#define ALT_V     303                                   /*  ALT + V         */
#define ALT_B     304                                   /*  ALT + B         */
#define ALT_N     305                                   /*  ALT + N         */
#define ALT_M     306                                   /*  ALT + M         */
#define F1        315                                   /*  F1              */
#define F2        316                                   /*  F2              */
#define F3        317                                   /*  F3              */
#define F4        318                                   /*  F4              */
#define F5        319                                   /*  F5              */
#define F6        320                                   /*  F6              */
#define F7        321                                   /*  F7              */
#define F8        322                                   /*  F8              */
#define F9        323                                   /*  F9              */
#define F10       324                                   /*  F10             */
#define CDOWN     336                                   /*  Cursor-Down     */
#define CHOME     327                                   /*  Cursor-Home     */
#define CUP       328                                   /*  Cursor-Up       */
#define CPGUP     329                                   /*  Cursor-Page Up  */
#define CLEFT     331                                   /*  Cursor-Left     */
#define CRIGHT    333                                   /*  Cursor-Right    */
#define CEND      335                                   /*  Cursor-End      */
#define CPGDN     337                                   /*  Cursor-Page Dn  */
#define INSERT    338                                   /*  INSERT          */
#define DEL       339                                   /*  DELETE          */
#define SHIFT_F1  340                                   /*  SHIFT + F1      */
#define SHIFT_F2  341                                   /*  SHIFT + F2      */
#define SHIFT_F3  342                                   /*  SHIFT + F3      */
#define SHIFT_F4  343                                   /*  SHIFT + F4      */
#define SHIFT_F5  344                                   /*  SHIFT + F5      */
#define SHIFT_F6  345                                   /*  SHIFT + F6      */
#define SHIFT_F7  346                                   /*  SHIFT + F7      */
#define SHIFT_F8  347                                   /*  SHIFT + F8      */
#define SHIFT_F9  348                                   /*  SHIFT + F9      */
#define SHIFT_F10 349                                   /*  SHIFT + F10     */
#define CTRL_F1   350                                   /*  CTRL + F1       */
#define CTRL_F2   351                                   /*  CTRL + F2       */
#define CTRL_F3   352                                   /*  CTRL + F3       */
#define CTRL_F4   353                                   /*  CTRL + F4       */
#define CTRL_F5   354                                   /*  CTRL + F5       */
#define CTRL_F6   355                                   /*  CTRL + F6       */
#define CTRL_F7   356                                   /*  CTRL + F7       */
#define CTRL_F8   357                                   /*  CTRL + F8       */
#define CTRL_F9   358                                   /*  CTRL + F9       */
#define CTRL_F10  359                                   /*  CTRL + F10      */
#define ALT_F1    360                                   /*  ALT + F1        */
#define ALT_F2    361                                   /*  ALT + F2        */
#define ALT_F3    362                                   /*  ALT + F3        */
#define ALT_F4    363                                   /*  ALT + F4        */
#define ALT_F5    364                                   /*  ALT + F5        */
#define ALT_F6    365                                   /*  ALT + F6        */
#define ALT_F7    366                                   /*  ALT + F7        */
#define ALT_F8    367                                   /*  ALT + F8        */
#define ALT_F9    368                                   /*  ALT + F9        */
#define ALT_F10   369                                   /*  ALT + F10       */
#define CTRL_LEFT 371                                   /*  CTRL-Left       */
#define CTRL_RIGHT 372                                  /*  CTRL-Right      */
#define CTRL_END  373                                   /*  CTRL-End        */
#define CTRL_PGDN 374                                   /*  CTRL-PgUp       */
#define CTRL_HOME 375                                   /*  CTRL-Home       */
#define ALT_1     376                                   /*  ALT + 1         */
#define ALT_2     377                                   /*  ALT + 2         */
#define ALT_3     378                                   /*  ALT + 3         */
#define ALT_4     379                                   /*  ALT + 4         */
#define ALT_5     380                                   /*  ALT + 5         */
#define ALT_6     381                                   /*  ALT + 6         */
#define ALT_7     382                                   /*  ALT + 7         */
#define ALT_8     383                                   /*  ALT + 8         */
#define ALT_9     384                                   /*  ALT + 9         */
#define ALT_0     385                                   /*  ALT + 0         */
#define CTRL_PGUP 388                                   /*  CTRL-PgUp       */
#define CTRL_UP   397                                   /*  CTRL-Up         */
#define CTRL_DOWN 401                                   /*  CTRL-Down       */
