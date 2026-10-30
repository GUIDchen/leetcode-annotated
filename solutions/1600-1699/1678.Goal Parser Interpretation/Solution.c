// 题目：1678. 设计 Goal 解析器（Goal Parser Interpretation）
// 思路：一次扫描 command，遇到 'G' 直接输出；遇到 '(' 时看下一个字符：')' 说明是 "()" 输出 'o'，否则是 "(al)" 输出 'a'、'l'。
// 时间复杂度：O(n)，每个字符只处理一次；空间复杂度：O(n)，结果字符串最长与输入等长。
char* interpret(char* command) {  // command：待解析的命令字符串，返回值是解析后的新字符串
    int n = strlen(command);  // 输入长度，也是输出长度的上界
    char* ans = malloc(sizeof(char) * n + 1);  // 为结果分配空间，加 1 留给结尾的 '\0'
    int i = 0;  // 结果字符串的写入下标
    for (int j = 0; j < n; j++) {  // 逐个字符扫描输入
        char c = command[j];  // 取出当前字符，便于多次比较
        if (c == 'G') {  // 情况一：普通字符 'G' 原样输出
            ans[i++] = 'G';  // 写入 'G' 后下标后移
        } else if (c == '(') {  // 情况二：遇到 '('，需要判断是 "()" 还是 "(al)"
            if (command[j + 1] == ')') {  // 下一个字符是 ')' 说明是空括号 "()"
                ans[i++] = 'o';  // 空括号解析为 'o'
            } else {  // 否则是 "(al)"
                ans[i++] = 'a';  // 先写入 'a'
                ans[i++] = 'l';  // 再写入 'l'
            }  // 内层 if-else 结束
        }  // 外层 if 结束：')' 什么都不输出
    }  // 扫描结束
    ans[i] = '\0';  // 补上字符串结束符
    return ans;  // 返回解析结果（由调用方负责释放）
}  // 函数结束