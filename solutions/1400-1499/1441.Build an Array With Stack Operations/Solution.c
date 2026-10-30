// 题目：1441. 用栈操作构建数组（Build an Array With Stack Operations）
// 思路：指针 cur 从 1 递增，target 中缺的数字用一次 Push 加一次 Pop 跳过，需要的数字只 Push。
// 时间复杂度：O(n)，最多产生 2n 次操作；空间复杂度：O(n)，结果数组最多 2n 个字符串指针。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** buildArray(int* target, int targetSize, int n, int* returnSize) {  // target 是目标数组，n 是可用整数的上界，*returnSize 输出操作个数
    char** ans = (char**) malloc(sizeof(char*) * (2 * n));  // 每个数字最多产生 Push、Pop 两次操作，所以 2n 个 char* 一定够用
    *returnSize = 0;  // 目前还没有写入任何操作
    int cur = 1;  // 下一个准备压入栈的整数，从 1 开始
    for (int i = 0; i < targetSize; i++) {  // 按顺序处理 target 的每个元素
        while (cur < target[i]) {  // cur 还没到 target[i]，说明 cur 不在目标里，要压入后弹出把它丢掉
            ans[(*returnSize)++] = "Push";  // 压入 cur（(*returnSize)++ 先取当前下标再自增）
            ans[(*returnSize)++] = "Pop";  // 立刻弹出，栈顶恢复原状，相当于跳过 cur
            cur++;  // 继续尝试下一个整数
        }
        ans[(*returnSize)++] = "Push";  // target[i] 是需要的数字，只做一次 Push 把它留在栈里
        cur++;  // 下一个数字从 target[i]+1 开始
    }
    return ans;  // 返回操作序列，调用者负责 free
}
