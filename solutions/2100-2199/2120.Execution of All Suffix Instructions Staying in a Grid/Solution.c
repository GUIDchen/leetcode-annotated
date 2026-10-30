// 题目：2120. 执行所有后缀指令（Execution of All Suffix Instructions Staying in a Grid）
// 核心思路：对每个后缀起点从题给起点重新模拟，一旦下一步越界就停止，成功走出的步数即该后缀答案。
// 时间复杂度：O(m^2)，m 为指令串长度，每个后缀最坏走满全程；空间复杂度：O(m)，需保存 m 个答案。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* executeInstructions(int n, int* startPos, int startPosSize, char* s, int* returnSize) {  // n：网格边长；startPos：起始坐标；s：指令串；returnSize：输出答案个数
    int m = strlen(s);  // 指令串长度，也就是需要处理的后缀个数
    int* ans = malloc(sizeof(int) * m);  // 为每个后缀分配一格的答案数组
    for (int i = 0; i < m; i++) {  // 枚举后缀起点 i，后缀为 s[i..m-1]
        int y = startPos[0];  // 每个后缀都从题给起点重新开始：y 是题面里的行坐标
        int x = startPos[1];  // x 是题面里的列坐标
        int j = i;  // j 记录实际执行到哪条指令，先指向后缀首字符
        for (j = i; j < m; j++) {  // 按顺序执行后缀里的每条指令
            if (s[j] == 'U') {  // 指令为向上
                y--;  // 源码约定：向上让 y 减一
            } else if (s[j] == 'D') {  // 指令为向下
                y++;  // 向下让 y 加一
            } else if (s[j] == 'L') {  // 指令为向左
                x--;  // 向左让 x 减一
            } else {  // 剩下的情况只可能是向右
                x++;  // 向右让 x 加一
            }
            if (y == -1 || y == n || x == -1 || x == n) {  // 每步只移动一格，越界时必然先命中这四个值之一
                break;  // 一旦越界立刻停止，后面的指令不再执行
            }
        }
        ans[i] = j - i;  // j 停在第一条越界指令上，j - i 恰好是成功执行的步数
    }
    *returnSize = m;  // 每个后缀都有一个答案，输出长度等于 m
    return ans;  // 返回 malloc 出来的答案数组，由判题器负责 free
}