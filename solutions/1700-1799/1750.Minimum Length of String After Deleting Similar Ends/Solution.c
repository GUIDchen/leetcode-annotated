// 题目：1750. 删除字符串两端相同字符后的最短长度（Minimum Length of String After Deleting Similar Ends）
// 核心思路：双指针 start、end 分别指向两端，只要两端字符相同就各自向中间推进、跳过整段相同的字符（一次删除必须把这段同字符全删掉），直到两端不同或指针相遇。
// 时间复杂度：O(n)，每个指针最多扫描一遍字符串；空间复杂度：O(1)，只使用常数个变量。
int minimumLength(char* s) {  // s：输入字符串；返回删除后能剩下的最短长度
    int n = strlen(s);  // 字符串长度，用于确定右端点初值
    int start = 0;  // 左指针，指向当前未删除部分的首字符
    int end = n - 1;  // 右指针，指向当前未删除部分的末字符
    while (start < end && s[start] == s[end]) {  // 两端字符相同才可能继续删除（不相同则无法再删）
        while (start + 1 < end && s[start] == s[start + 1]) {  // 从左端跳过与 s[start] 相同的整段字符
            start++;  // 左指针右移，跳过相同字符
        }  // 左端整段相同字符已定位到最后一个
        while (start < end - 1 && s[end] == s[end - 1]) {  // 从右端跳过与 s[end] 相同的整段字符
            end--;  // 右指针左移，跳过相同字符
        }  // 右端整段相同字符已定位到第一个
        start++;  // 一次性删除左端这一整段
        end--;  // 一次性删除右端这一整段
    }  // 继续检查新的两端是否仍相同
    if (start > end) {  // 指针交叉说明整串都被删光
        return 0;  // 空串长度为 0
    }  // 判断结束
    return end - start + 1;  // 剩下的部分 [start, end] 的长度
}  // 函数结束