// 题目：1502. 判断能否形成等差数列（Can Make Arithmetic Progression From Sequence）
// 思路：先升序排序，公差取前两个元素之差，再逐个检查后续相邻差是否都等于该公差。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(log n)，qsort 的递归栈开销。
int cmp(const void* a, const void* b) {  // 升序比较函数，供 qsort 调用
    return *(int*) a - *(int*) b;  // 相减的正负号即大小关系；本题值域小，不会溢出 int
}

bool canMakeArithmeticProgression(int* arr, int arrSize) {  // arr：输入数组（会被原地排序）；arrSize：元素个数；返回能否构成等差数列
    qsort(arr, arrSize, sizeof(int), cmp);  // 原地排序：等差序列排序后，相邻元素之差必然处处相等
    int d = arr[1] - arr[0];  // 公差取排序后前两个元素之差（题目保证 arrSize >= 2）
    for (int i = 2; i < arrSize; i++) {  // 从第三个元素开始逐个校验
        if (arr[i] - arr[i - 1] != d) {  // 当前相邻差与公差不同
            return 0;  // 不满足等差，返回 false（C 里用 0 表示）
        }
    }
    return 1;  // 所有相邻差都等于公差，返回 true（C 里用 1 表示）
}
