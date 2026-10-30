// 题目：1356. 根据数字二进制下 1 的数目排序（Sort Integers by The Number of 1 Bits）
// 思路：手写 lowbit 技巧统计每个数的 1 的个数，再用 qsort 按「1 的个数优先、数值其次」排序。
// 时间复杂度：O(n log n * log W)，每个数统计与比较都要扫描二进制位，W ≤ 32；空间复杂度：O(n)，需要一个结果数组。
static int bitCount(int x) {  // 统计整数 x 的二进制表示中 1 的个数
    int cnt = 0;  // 计数器清零
    while (x) {  // 只要 x 还非 0 就继续消位
        x &= (x - 1);  // x &= x-1 会消掉最低位的 1，每循环一次就少一个 1
        ++cnt;  // 计数加一
    }  // 循环结束时 cnt 就是 1 的个数
    return cnt;  // 返回统计结果
}  // bitCount 结束

static int cmp(const void* a, const void* b) {  // qsort 的比较函数：先按 1 的个数升序，个数相同再按数值升序
    int x = *(const int*) a;  // 把 void* 转成 int* 后取出第一个元素
    int y = *(const int*) b;  // 取出第二个元素

    int cx = bitCount(x);  // 第一个元素中 1 的个数
    int cy = bitCount(y);  // 第二个元素中 1 的个数

    if (cx != cy) {  // 1 的个数不同时，它就是第一关键字
        return cx - cy;  // 1 的个数少的排在前面
    }  // 1 的个数相同时，退回按数值比较
    return x - y;  // 数值小的排在前面
}  // cmp 结束

/**  // 下面是判题器关于内存所有权的约定：返回数组由本函数 malloc，调用方负责 free
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortByBits(int* arr, int arrSize, int* returnSize) {  // 返回按 1 的个数排序后的新数组，*returnSize 输出结果长度
    *returnSize = arrSize;  // 结果长度与输入长度相同

    int* res = (int*) malloc(sizeof(int) * arrSize);  // 申请结果数组：判题器要求返回的内存由本函数分配
    if (!res) {  // 内存分配失败的保护
        return NULL;  // 返回空指针表示失败
    }  // 分配成功，继续

    for (int i = 0; i < arrSize; ++i) {  // 逐个复制输入元素
        res[i] = arr[i];  // 复制到结果数组，避免改动调用方的数据
    }  // 复制完成

    qsort(res, arrSize, sizeof(int), cmp);  // 用自定义比较函数原地排序

    return res;  // 返回排好序的新数组，所有权交给调用方
}  // sortByBits 结束
