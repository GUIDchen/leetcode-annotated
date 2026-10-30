// 题目：1598. 文件夹操作日志搜集器（Crawler Log Folder）
// 思路：维护当前目录深度，"../" 让深度减一（不低于 0），"./" 不变，其余目录名让深度加一。
// 时间复杂度：O(n)，只需扫一遍日志；空间复杂度：O(1)，只用一个深度变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏：取两个值中较大的一个（判题环境未提供 max，需要自带）

// 注意：本题是判题片段，没有 main，由判题器调用 minOperations
int minOperations(char** logs, int logsSize) {  // logs 为日志字符串数组，logsSize 为条数；返回最终深度
    int depth = 0;  // 当前目录相对主目录的深度，从 0 开始
    for (int i = 0; i < logsSize; i++) {  // 逐条处理日志
        char* log = logs[i];  // 取出第 i 条日志字符串
        if (!strcmp(log, "../")) {  // strcmp 返回 0 表示内容相同，即这是一次返回父目录的操作
            depth = max(0, depth - 1);  // 深度减一，但不能减到负数（主目录已经是最上层）
        } else if (strcmp(log, "./")) {  // 与 "./" 比较不为 0 且与 "../" 不同，说明是普通子文件夹名
            depth++;  // 进入子文件夹，深度加一
        }  // 分支判断结束（"./" 既不加深也不减少，直接忽略）
    }  // 日志遍历结束
    return depth;  // 返回最终深度，也就是回到主目录所需的最少操作次数
}  // 函数结束