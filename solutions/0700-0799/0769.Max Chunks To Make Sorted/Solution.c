// 题目：769. 最多能完成排序的块（Max Chunks To Make Sorted）
// 核心思路：arr 是 0..n-1 的排列，前缀最大值 mx 恰好等于下标 i 时，前 i+1 个数正好是 0..i，可以切一刀。
// 时间复杂度 O(n)（一次线性扫描）；空间复杂度 O(1)（只用到常数个整型变量）。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏定义：取 a、b 中较大者，参数都加括号防止展开后优先级出错

int maxChunksToSorted(int* arr, int arrSize) {  // arr：0..n-1 的排列；arrSize：数组长度；返回最多能切分的块数
    int ans = 0;  // ans 记录已经切出的块数
    int mx = -1;  // mx 记录前缀最大值，初始化 -1 表示还没有任何元素（元素均非负）
    for (int i = 0; i < arrSize; i++) {  // 从左到右扫描每个下标 i
        mx = max(mx, arr[i]);  // 更新前 i+1 个元素的最大值
        if (mx == i) {  // 前缀最大值正好等于下标，说明前 i+1 个元素恰好是 0..i 的一个排列
            ans++;  // 此时可以安全地在 i 之后切一刀，块数加一
        }  // if 分支结束
    }  // for 循环结束
    return ans;  // 返回最多块数
}  // 函数结束
