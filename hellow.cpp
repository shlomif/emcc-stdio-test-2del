
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

#ifdef REMOVE
void sync_idbfs() {
    EM_ASM(
        FS.syncfs(false,function (err) {});
    );
}

extern "C" void EMSCRIPTEN_KEEPALIVE test(){
    FILE* fp = fopen("/working1/twrite.txt", "rt");
    if(!fp){
      fp = fopen("/working1/twrite.txt", "a");
    }

    if (fp) {
        fprintf(fp, "This is twrite.txt.\n");
        fclose(fp);
    }

    FILE* fp1 = fopen("/working1/working2/twrite1.txt", "rt");
    if(!fp1){
      fp1 = fopen("/working1/working2/twrite1.txt", "a");
    }

    if (fp1) {
        fprintf(fp1, "This is twrite1.txt.\n");
        fclose(fp1);
    }

    FILE* fp2 = fopen("/working1/twrite2.txt", "rt");
    if(!fp2){
      fp2 = fopen("/working1/twrite2.txt", "a");
    }

    if (fp2) {
        fprintf(fp2, "This is twrite2.txt.\n");
        fclose(fp2);
    }


}

void util_create(){
    test();
}

void read_fs(const char* fname) {
    FILE* fp = fopen(fname, "rt");
    if(!fp){
      printf("cannot open file");
    }
    if (fp) {
        while (!feof(fp)) {
            char c = fgetc(fp);
            if (c != EOF) {
                putchar(c);
            }
        }
        fclose(fp);
    }
}

void write_fs() {

    FILE* fp = fopen("t3.txt", "a");
    if (fp) {
        fprintf(fp, "This is t3.txt.\n");
        fclose(fp);
    }
}
#endif

int main() {
    printf("testing started\n");
#ifdef REMOVE
    write_fs();

    EM_ASM(
        FS.mkdir('/working1');
        FS.mount(IDBFS, {}, '/working1');

        FS.syncfs(true, function (err) {
          assert(!err);
        });
    );

    util_create();

    sync_idbfs();

    printf("Second time reading testing started after appending\n");
    read_fs("/working1/twrite.txt");

    printf("Third time reading testing started after appending\n");
    read_fs("/working1/twrite2.txt");
    read_fs("/working1/working2/twrite1.txt");
#endif
    return 0;
}
