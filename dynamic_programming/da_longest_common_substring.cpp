#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b ? a : b);
}

int longest_common_substring(char *str1, char *str2) {
    int m = strlen(str1), n = strlen(str2);

    int dp[m + 1][n + 1];
    int max_length = 0; // Length of the longest common substring
    int end_position = 0; // Ending position of the longest common substring

    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            if(i == 0 || j == 0){
                dp[i][j] = 0;

            } else if(str1[i - 1] == str2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if(dp[i][j] > max_length){
                    max_length = dp[i][j];
                    end_position = i - 1;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Extract the longest common substring
    char longest_substring[max_length + 1];
    strncpy(longest_substring, str1 + end_position - max_length + 1, max_length);
    longest_substring[max_length] = '\0';

    printf("Longest Common Substring: %s\n", longest_substring);

    return max_length;
}

int main() {
    char str1[] = "10010101", str2[] = "010110110";

    int length = longest_common_substring(str1, str2);
    printf("Length of Longest Common Substring: %d\n", length);

    return 0;
}
