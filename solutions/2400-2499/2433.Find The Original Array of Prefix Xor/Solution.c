// 题目：2433. 找出前缀异或的原始数组（Find The Original Array of Prefix Xor）
// 思路：由 pref[i] = pref[i-1] ^ arr[i] 两边同异或 pref[i-1]，得 arr[i] = pref[i-1] ^ pref[i]；arr[0] 就等于 pref[0]。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(n)，除必须返回的数组外只用常数级变量。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findArray(int* pref, int prefSize, int* returnSize) {  // pref：前缀异或数组；returnSize：输出答案数组长度
    int* res = (int*) malloc(sizeof(int) * prefSize);  // 按题目要求用 malloc 分配返回数组，长度与原数组相同
    res[0] = pref[0];  // 首元素特殊处理：arr[0] 就等于 pref[0]
    for (int i = 1; i < prefSize; i++) {  // 从第二个元素开始逐个还原
        res[i] = pref[i - 1] ^ pref[i];  // 异或的自反性：pref[i-1] ^ pref[i] 正好抵消掉公共前缀，留下 arr[i]
    }
    *returnSize = prefSize;  // 把答案长度写回调用者的返回长度参数
    return res;  // 返回答案数组的指针，由调用者负责 free
}