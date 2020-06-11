#include "myreadelf.h"
//

//
int main(int argc, char** argv){
    debug_print("test\n");
    
    if(argc>1){  
       for(arg_action* action = parse_arg(argc,  argv) ;
        action->next != NULL ;
         action = action->next){
            if( action->num == FLAG__file_header ){
               for(int i = 0 ; i < count_files ; i++ ){
                    printf(":: %s :: ELF header ::\n",ELF_FILES[i]);
                    read_elf_header( ELF_FILES[i] );
               }
            }
            if(action->num == FLAG_x || action->num == FLAG__hex_dump ){
               for(int i = 0 ; i < count_files ; i++ ){
                    printf(":: %s :: dump section %s ::\n",ELF_FILES[i],action->option);
                    read_elf_section( ELF_FILES[i], action->option );
               }
            }
        }
    }else{
        printf("%s",USAGE);
        return -1;
    }
    return 0;
}
//
arg_action* parse_arg(int argc, char** argv){
    int i_flag=-1;
    int i = 1;
    arg_action* action = new_action();
    arg_action* action0 = action;
    while(i<argc){
        
             if(0==strcmp(flag_H.str,argv[i])            ){i_flag = flag_H.num;}
        else if(0==strcmp(flag_help.str,argv[i])         ){i_flag = flag_help.num;}
        else if(0==strcmp(flag_h.str,argv[i])            ){i_flag = flag_h.num;}
        else if(0==strcmp(flag__file_header.str,argv[i]) ){i_flag = flag__file_header.num;}
        else if(0==strcmp(flag_x.str,argv[i])            ){i_flag = flag_x.num;}
        else if(0==memcmp(flag__hex_dump.str,argv[i],10)    ){i_flag = flag__hex_dump.num;}
        else{i_flag = FLAG_FILE;}
        switch (i_flag){

            case FLAG_H:
            case FLAG__help:
                debug_print("(DEBUG) parse arg, print usage\n");
                // help
                printf("%s",USAGE);
                exit(0);

            case FLAG_h:
            case FLAG__file_header:
                debug_print("(DEBUG) parse arg, dump header\n");
                // action dump header
                action->num    = FLAG__file_header;
                action->next   = new_action();
                action         = action->next;
                i++;
                break;
            
                
            case FLAG_x:
                debug_print("(DEBUG) parse arg, -x : dump section hex\n");
                action->num    = FLAG_x;
                action->option = argv[i+1];
                action->next   = new_action();
                action         = action->next;
                i+=2;
                break;

            case FLAG__hex_dump:
                debug_print("(DEBUG) parse arg, --hex-dump : dump section hex\n");
                // action dump hex section
                action->num    = FLAG__hex_dump;
                action->option = argv[i]+11;
                action->next   = new_action();
                action         = action->next;
                i++;
                break;
            
            case FLAG_FILE:
                sprintf(debug_str, "(DEBUG) parse file: %s\n", argv[i]);
                debug_print(debug_str);
                // save filename             
                count_files++;
                i++;
                break;
                

            default:
                break;
        }
    }
    ELF_FILES = malloc(sizeof(char*)*count_files);
    for(int i = 0; i < count_files ; i++){
        ELF_FILES[i] = malloc(sizeof(char)*strlen(argv[i+argc-count_files]));
        ELF_FILES[i] = argv[i+argc-count_files];
        sprintf(debug_str, "(DEBUG) Files (argv): %s\n",argv[i+argc-count_files]);
        debug_print(debug_str);
        sprintf(debug_str, "(DEBUG) Files (ELF_FILES): %s\n",ELF_FILES[i]);
        debug_print(debug_str);
    }
    return action0;
}
//
arg_action* new_action(){
    arg_action* action = malloc(sizeof(arg_action));
    action->next = NULL;
    action->num = -1;
    action->option = "\0";
    return action;
}

