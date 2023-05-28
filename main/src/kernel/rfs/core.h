/*
 --------------------------------------
 - THIS IS THE FILE SYSTEM MANAGEMENT -
 -------------------------------------- 
*/
struct _SYS_FILE_ {
    String fname = "untitled"; // File name on FS
    bool PERM_EXEC_ = true; // So as the OS needs a way of reading
    bool PERM_WRITE_= true; // and writing files I'm implementing
    bool PERM_READ_ = true; // a temporal file system
    String content = "";    // this will allow to write files in ram
    _SYS_FILE_ *parent;
};

class _Ram_File_System_ {
    public:
    _SYS_FILE_ *space[100]; // This is where the temporal files will be stored
    int _WRITING_PTR_ = 0;  // and as the user moves they will be written 
    _Ram_File_System_ (int);// this is the constructor, empty as there are no startup routines
    void _RFS_SETUP_ ();    // this is the actual setup that goes on the kernel systemd startup
    void _RFS_WRITE_ (bool _pr, bool _pw, bool _pe, String content, String _fname);
    void _RFS_FLUSH_ ();    // clean all files in the system
};

_Ram_File_System_ :: _Ram_File_System_(int nil) {};

void _Ram_File_System_ :: _RFS_SETUP_ () {
    Serial.println("(System) initializing file system manager...");
}

void _Ram_File_System_ :: _RFS_WRITE_ (bool _pr, bool _pw, bool _pe, String _content, String _fname) {
    _SYS_FILE_ *tmp_file =  new _SYS_FILE_ (); // SO WE CREATE A TEMPORAL FILE ARCHIVE IN RAM
    // -------------------------------------------
      tmp_file->PERM_EXEC_ = _pe;
      tmp_file->PERM_READ_ = _pr;       // WE SET THE PERMISIONS AND FILE PROPERTIES FOR OUR
      tmp_file->PERM_WRITE_ = _pw;      // FILES AND 
      tmp_file->fname = _fname;
      tmp_file->content = _content;
    // -------------------------------------------
    space[_WRITING_PTR_] = tmp_file;
} 

void _Ram_File_System_ ::_RFS_FLUSH_(){
      for(int i = 0; i < 100; i++){
        if(space[i] != NULL){
            _SYS_FILE_ *tmp_del = new _SYS_FILE_();
            space[i]->parent = tmp_del;
            delete tmp_del;
        }
      }
      _WRITING_PTR_ = 0; 
}

_Ram_File_System_ *RFS = new _Ram_File_System_ (0);