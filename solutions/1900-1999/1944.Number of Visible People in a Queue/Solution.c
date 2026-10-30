// 题目：1944. 队列中可以看到的人数（Number of Visible People in a Queue）
// 思路：从队尾往前扫描，用单调递减栈保存右侧还没被挡住的候选身高；比当前人矮的全部出栈并各计一次可见，栈顶若还留有更高的人再计一次。
// 时间复杂度：O(n)，每个下标最多入栈出栈各一次；空间复杂度：O(n)，栈与返回数组。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 该函数无 main：属于 LeetCode 判题器调用的片段，返回数组由判题器负责 free
int* canSeePersonsCount(int* heights, int heightsSize, int* returnSize) {  // heights：身高数组；returnSize：输出返回数组的长度
    int* ans = malloc(sizeof(int) * heightsSize);  // 按人数分配答案数组，ans[j] 表示第 j 个人向右能看到的人数
    memset(ans, 0, sizeof(int) * heightsSize);  // 先把答案全部清零，之后逐个累加
    int stack[heightsSize];  // 数组模拟栈：栈里存下标，对应的身高从栈底到栈顶单调递减；VLA 长度由人数决定
    int i = 0;  // i 是栈内元素个数，同时是栈顶的下一个空位
    for (int j = heightsSize - 1; j >= 0; j--) {  // 从队尾（最右侧）往前遍历，j 是当前处理的人
        while (i) {  // 栈非空就一直判断栈顶那个人是否可见
            ans[j]++;  // 栈顶那个人可以被 j 看到（他比 j 矮，不挡视线）
            if (heights[j] <= heights[stack[i - 1]]) {  // 若 j 不比栈顶更高，说明他挡住了更左边的人
                break;  // 此时视线终止：栈顶是本次能看到的最后一个人（已在上方计数）
            }  // if 代码块结束：没 break 就执行下面的出栈
            i--;  // 栈顶比 j 矮，会被 j 完全遮挡，弹出后继续看更右边
        }  // while 结束：栈顶已是当前人能看到的最远/最高的人
        stack[i++] = j;  // 把 j 压栈，作为更左边的人向右看时的候选
    }  // 遍历结束，所有人的可见人数都统计完
    *returnSize = heightsSize;  // 输出返回数组长度：每人一个答案
    return ans;  // 返回答案数组，判题器负责 free
}