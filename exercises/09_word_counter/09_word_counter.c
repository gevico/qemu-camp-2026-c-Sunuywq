#include <stdio.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码
    int i = 0;
    int in_word = 0;
    
    while (str[i] != '\0'){
    	if (str[i] == ' ') {
		in_word = 0;
	
	}

	else if (in_word == 0){
		in_word = 1;
		wordCount++;
	}
	i++;
    
    }

    printf("单词数量: %d\n", wordCount);
    
    return 0;
}
