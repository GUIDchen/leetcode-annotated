// 题目：6. Z 字形变换（Zigzag Conversion）
// 思路：每行开一个缓冲区，用方向变量 k 让行号在 0 与 numRows-1 之间来回折返，边遍历边把字符收进对应行，最后按行拼接。
// 时间复杂度：O(n)，每个字符写入、读出各一次；空间复杂度：O(n)，各行的缓冲区合计存 n 个字符。
char* convert(char* s, int numRows) {  // s 为输入字符串，numRows 为 Z 字形行数，返回按行读取后的新串
    if (numRows == 1) {  // 只有一行时，Z 字形就是原串本身
        return strdup(s);  // 复制一份返回，保持「返回值由调用方释放」的约定
    }

    int len = strlen(s);  // 字符串长度
    char** g = (char**) malloc(numRows * sizeof(char*));  // g[r] 指向第 r 行的字符缓冲区
    int* idx = (int*) malloc(numRows * sizeof(int));  // idx[r] 记录第 r 行已经写入的字符个数
    for (int i = 0; i < numRows; ++i) {  // 逐行申请缓冲区
        g[i] = (char*) malloc((len + 1) * sizeof(char));  // 一行最多放 len 个字符，再留一字节给 '\0'
        idx[i] = 0;  // 该行写指针清零
    }

    int i = 0, k = -1;  // i 是当前行号，k 是行号的变化方向（+1 向下，-1 向上）
    for (int p = 0; p < len; ++p) {  // 按原串顺序处理每个字符
        g[i][idx[i]++] = s[p];  // 把字符放进第 i 行，并让该行写指针后移
        if (i == 0 || i == numRows - 1) {  // 走到最上一行或最下一行，需要折返
            k = -k;  // 方向取反
        }
        i += k;  // 沿方向移动到下一行
    }

    char* ans = (char*) malloc((len + 1) * sizeof(char));  // 结果缓冲区：len 个字符加一个 '\0'
    int pos = 0;  // 结果的写入位置
    for (int r = 0; r < numRows; ++r) {  // 按行号从小到大拼接
        for (int j = 0; j < idx[r]; ++j) {  // 遍历第 r 行已收集的字符
            ans[pos++] = g[r][j];  // 逐个搬到结果里，并让写位置前移
        }
        free(g[r]);  // 这一行搬完即可释放
    }
    ans[pos] = '\0';  // 补上字符串结束符

    free(g);  // 释放行指针数组
    free(idx);  // 释放行长度数组
    return ans;  // 返回 Z 字形按行读取的结果
}
