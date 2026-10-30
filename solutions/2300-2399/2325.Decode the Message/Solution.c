// 题目：2325. 解密消息（Decode the Message）
// 核心思路：按 key 中字母首次出现的顺序建立「密文字母 -> 明文字母」的映射表，再用它逐字符解密 message。
// 时间复杂度：O(m + n)，m、n 分别为 key 与 message 的长度；空间复杂度：O(1)，映射表固定只有 26 个字符。
char* decodeMessage(char* key, char* message) {  // key：密码表；message：待解密的密文
    int m = strlen(key);  // 密码表长度
    int n = strlen(message);  // 密文长度
    char d[26];  // 映射表：下标 0~25 对应密文字母 a~z
    memset(d, ' ', 26);  // 先用空格填充，表示这些字母尚未建立映射
    for (int i = 0, j = 0; i < m; i++) {  // i 扫描密码表，j 记录下一个要分配的明文字母序号
        if (key[i] == ' ' || d[key[i] - 'a'] != ' ') {  // 跳过空格，以及已经建立过映射的重复字母
            continue;  // 直接处理下一个字符
        }  // 结束本轮判断
        d[key[i] - 'a'] = 'a' + j++;  // 首次出现的字母依次映射为 a、b、c……，随后 j 自增
    }  // 结束建表循环
    char* ans = malloc(n + 1);  // 为 n 个字符加结尾符申请空间
    for (int i = 0; i < n; i++) {  // 逐字符解密
        ans[i] = message[i] == ' ' ? ' ' : d[message[i] - 'a'];  // 空格原样保留，其余字母查表替换
    }  // 结束解密循环
    ans[n] = '\0';  // 补上字符串结束符
    return ans;  // 返回解密结果（由调用方释放）
}