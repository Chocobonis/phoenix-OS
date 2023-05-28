void _SYS_BONYX_WTD_RESET_ () {

}

void _SYS_WRITE_ (String sys_content){
    char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";
    String _rname = "file";
    for(int i = 0; i < 8; i++){
        byte randomValue = random(0, 37);
        char letter = randomValue + 'a';
        if(randomValue > 26) { 
         letter = (randomValue - 26) + '0';
        }
        _rname = _rname + letter;
    }
    RFS->_RFS_WRITE_ (true, true, true, sys_content, _rname);
    /*
        I KNOW THAT THIS FUNCTION AT FIRST MAY SEEM USELESS, BUT IT AIMS TO WORK
        AS A WRAPPER FOR THE FUNCTION ON THE CLASS FOR FASTER ACCESS, AND POSSIBILITY
        TO CALL IT FROM ARRAY
    */
}