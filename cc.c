#include <stdio.h>
#include <string.h>

int main(){

	char str1[101], str2[101];
	int cnt = 0;

	gets(str1);
	gets(str2);

	//str2가 str1에 몇번 나타나는지 cnt 계산해서 출력 하는 문제
	int f = 0;
	//같으면 그대로 0 다르면 1로 반환하자 

	for (int i = 0; i < strlen(str1); i ++){//str1 길이 만큼 포문을 돌려서 확인하는거지
		for (int j = 0; j < strlen(str2); j ++){

			if (str1[i+j]==str2[j]) f = 0; 
			else{
				f = 1;
				break;
			}
		}
		if (f == 0){//그대로 0이면 
			i+=strlen(str2)-1;k
			cnt++;
		}
	}

	printf("%d", cnt);
	return 0;
}