// 题目：1828. 统计一个圆中点的数目（Queries on Number of Points Inside a Circle）
// 思路：对每个查询枚举所有点，用欧氏距离与半径比较，距离不超过半径即计入答案。
// 时间复杂度：O(q * p)，q、p 分别为查询数与点数；空间复杂度：O(q)，存放每个查询的答案。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */  // 题面注释：返回数组由本函数 malloc，调用方负责释放
int* countPoints(int** points, int pointsSize, int* pointsColSize, int** queries, int queriesSize, int* queriesColSize,  // 参数：points 是点集；queries 每行是 [圆心 x, 圆心 y, 半径]
    int* returnSize) {  // 续行：returnSize 用于输出结果数组长度；返回每个查询命中的点数
    int* ans = malloc(sizeof(int) * queriesSize);  // 为每个查询分配一个存放结果的槽位
    for (int i = 0; i < queriesSize; i++) {  // 逐个查询处理
        int cx = queries[i][0];  // 当前查询的圆心横坐标
        int cy = queries[i][1];  // 当前查询的圆心纵坐标
        int r = queries[i][2];  // 当前查询的半径
        int count = 0;  // 当前查询命中的点数
        for (int j = 0; j < pointsSize; j++) {  // 枚举所有点
            if (sqrt(pow(points[j][0] - cx, 2) + pow(points[j][1] - cy, 2)) <= r) {  // 点到圆心的欧氏距离不超过半径，即在圆内（含边界）
                count++;  // 命中点数加一
            }  // 判断结束
        }  // 点集遍历结束
        ans[i] = count;  // 保存该查询的答案
    }  // 查询遍历结束
    *returnSize = queriesSize;  // 输出结果数组的长度
    return ans;  // 返回结果数组
}  // 函数结束