#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define SYS_2D_CPY 451

int main(){
    float src_arr[2][2]= {{1.0,2.0},{3.0,4.0}};
    float arr_destination[2][2];

    float sys_call= syscall(SYS_2D_CPY,src_arr, arr_destination,2,2);

    if(sys_call== 0){
        printf("Message : No error in copying\n");
    }else if(sys_call== -1){
        printf("Message: Error in copying\n");
    }

    for(int i=0;i<2;i++){
        for(int j =0; j<2;j++){
            printf("%f ", arr_destination[i][j]);
        }
        printf("\n");
    }
    return 0;
}