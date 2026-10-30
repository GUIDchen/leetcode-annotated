// 题目：1796. 字符串中第二大的数字（Second Largest Digit in a String）
// 思路：一遍扫描，用 first / second 分别维护最大与严格次大的数字，遇到数字就按大小关系更新。
// 时间复杂度：O(n)，只扫一遍；空间复杂度：O(1)，只用两个变量。
int secondHighest(char* s) {  // s：以 '\0' 结尾的字符串，返回第二大的数字，不存在则返回 -1
    int first = -1;  // 最大数字，-1 表示还没遇到任何数字
    int second = -1;  // 第二大数字（严格小于最大值）
    for (int i = 0; s[i]; i++) {  // 以 '\0' 作为循环结束条件，逐字符扫描
        if (isdigit(s[i])) {  // 只处理数字字符
            int num = s[i] - '0';  // 把数字字符转成 0~9 的整数值
            if (num > first) {  // 出现了新的最大值
                second = first;  // 原来的最大值退居第二
                first = num;  // 更新最大值
            } else if (num < first && second < num) {  // 既不等于最大值又比当前第二大更大，才更新
                second = num;  // 更新第二大数字
            }  // if 结束
        }  // if 结束
    }  // for 结束
    return second;  // 没有第二大时自然返回 -1
}  // 函数结束