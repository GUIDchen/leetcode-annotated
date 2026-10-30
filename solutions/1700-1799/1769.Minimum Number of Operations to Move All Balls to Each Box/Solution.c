// 题目：1769. 移动所有球到每个盒子所需的最小操作数（Minimum Number of Operations to Move All Balls to Each Box）
// 思路：前后缀递推。left[i] 记录 i 左侧所有球移到 i 的代价，right[i] 记录右侧的代价，两者相加就是该盒子所需的最小操作数；扫描时用已出现的球数 count 做增量累加。
// 时间复杂度：O(n)，共三次线性扫描；空间复杂度：O(n)，left、right、ans 三个数组。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minOperations(char* boxes, int* returnSize) {  // boxes 是只含 '0'/'1' 的字符串，returnSize 输出结果长度；返回每个盒子所需的最小操作数
    int n = strlen(boxes);  // 盒子的个数
    int* left = malloc(sizeof(int) * n);  // left[i] 表示把 i 左侧的所有球移到 i 所需的操作数
    int* right = malloc(sizeof(int) * n);  // right[i] 表示把 i 右侧的所有球移到 i 所需的操作数
    memset(left, 0, sizeof(int) * n);  // left 数组清零，保证初值为 0
    memset(right, 0, sizeof(int) * n);  // right 数组清零，保证初值为 0
    for (int i = 1, count = 0; i < n; i++) {  // 从左往右扫描，count 表示 i 左侧已经出现的球数
        if (boxes[i - 1] == '1') {  // 上一个盒子里有球
            count++;  // 左侧球数加一
        }
        left[i] = left[i - 1] + count;  // 递推：左侧代价 = 左一格的代价 + 左侧球数（每个球都要多走一步）
    }
    for (int i = n - 2, count = 0; i >= 0; i--) {  // 从右往左扫描，count 表示 i 右侧已经出现的球数
        if (boxes[i + 1] == '1') {  // 下一个盒子里有球
            count++;  // 右侧球数加一
        }
        right[i] = right[i + 1] + count;  // 递推：右侧代价 = 右一格的代价 + 右侧球数
    }
    int* ans = malloc(sizeof(int) * n);  // 答案数组，由判题器负责 free
    for (int i = 0; i < n; i++) {  // 逐盒计算答案
        ans[i] = left[i] + right[i];  // 左右两侧的搬运代价相加即该盒子的总操作数
    }
    free(left);  // 释放临时数组 left
    free(right);  // 释放临时数组 right
    *returnSize = n;  // 输出结果长度
    return ans;  // 返回答案数组
}  // 函数结束