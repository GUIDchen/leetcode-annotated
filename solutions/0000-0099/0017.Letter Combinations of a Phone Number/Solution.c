// 题目：17. 电话号码的字母组合（Letter Combinations of a Phone Number）
// 思路：自底向上做笛卡尔积，ans 保存已经拼好的所有前缀，每读一位数字就用它的候选字母把每个前缀扩展一遍。
// 时间复杂度：O(4^n · n)，每个组合长度 n，分支因子最多 4；空间复杂度：O(4^n · n)，存放全部结果。
char* d[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};  // 下标 0..7 依次对应数字 2..9 的候选字母

char** letterCombinations(char* digits, int* returnSize) {  // digits 是数字串，*returnSize 输出组合个数
    if (!*digits) {  // 数字串为空
        *returnSize = 0;  // 没有组合
        return NULL;  // 按题目要求返回空
    }

    int size = 1;  // 当前已有的前缀个数，初始是空串这一个前缀
    char** ans = (char**) malloc(sizeof(char*));  // 结果指针数组，先只放一个元素
    ans[0] = strdup("");  // 空串作为笛卡尔积的单位元

    for (int x = 0; digits[x]; ++x) {  // 逐位处理数字串
        char* s = d[digits[x] - '2'];  // 取出该数字对应的候选字母（'2' 映射到下标 0）
        int len = strlen(s);  // 本位的候选字母个数
        char** t = (char**) malloc(sizeof(char*) * size * len);  // 新一层的数组，最多容纳 size * len 个组合
        int tSize = 0;  // 新一层的实际组合个数

        for (int i = 0; i < size; ++i) {  // 遍历上一层每个前缀
            for (int j = 0; j < len; ++j) {  // 遍历本位的每个候选字母
                int oldLen = strlen(ans[i]);  // 原前缀长度
                char* tmp = (char*) malloc(oldLen + 2);  // 新串：原前缀 + 1 个字母 + '\0'
                strcpy(tmp, ans[i]);  // 复制原前缀
                tmp[oldLen] = s[j];  // 在末尾接上当前字母
                tmp[oldLen + 1] = '\0';  // 补上字符串结束符
                t[tSize++] = tmp;  // 新组合放入新一层数组
            }
            free(ans[i]);  // 该前缀已被所有候选字母扩展过，及时释放避免泄漏
        }
        free(ans);  // 释放上一层的指针数组
        ans = t;  // 用新一层替换旧一层
        size = tSize;  // 更新组合个数
    }

    *returnSize = size;  // 输出最终组合个数
    return ans;  // 返回所有字母组合
}
