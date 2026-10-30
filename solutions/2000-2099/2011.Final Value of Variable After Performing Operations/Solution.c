// 题目：2011. 执行操作后的变量值（Final Value of Variable After Performing Operations）
// 思路：四个操作串只有第 2 个字符不同，'+' 表示加 1、'-' 表示减 1，遍历累加即得最终值。
// 时间复杂度：O(n)，n 为操作个数；空间复杂度：O(1)，只用一个累加变量。
int finalValueAfterOperations(char** operations, int operationsSize) {  // operations：操作字符串数组；operationsSize：操作个数；返回变量 X 的最终值
    int ans = 0;  // ans 保存变量 X 的当前值，初始为 0
    for (int i = 0; i < operationsSize; i++) {  // 从左到右依次处理每一个操作
        ans += operations[i][1] == '+' ? 1 : -1;  // 下标 1 是 '+' 说明是 "++X"/"X++"，否则是 "--X"/"X--"
    }  // 循环体结束
    return ans;  // 返回全部操作执行完后 X 的值
}  // 函数结束