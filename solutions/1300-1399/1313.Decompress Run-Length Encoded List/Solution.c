// 题目：1313. 解压缩编码列表（Decompress Run-Length Encoded List）
// 核心思路：nums 按 (频次, 值) 成对出现；先累加所有频次得到答案长度，再第二遍展开逐对写入。
// 时间复杂度：O(n + 答案长度)，两遍线性扫描；空间复杂度：O(答案长度)，结果数组必须 malloc。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* decompressRLElist(int* nums, int numsSize, int* returnSize) {  // nums 是编码数组，returnSize 用于回填答案长度
    int n = 0;  // 累加展开后的总长度
    for (int i = 0; i < numsSize; i += 2) {  // 每隔两个元素取一次频次
        n += nums[i];  // 频次累加进总长度
    }
    int* ans = (int*) malloc(n * sizeof(int));  // 按总长度一次性分配结果数组
    *returnSize = n;  // 回填长度，判题器据此读取返回数组
    int k = 0;  // 结果数组的写指针
    for (int i = 0; i < numsSize; i += 2) {  // 再次成对扫描编码数组
        int freq = nums[i];  // 本组的重复次数
        int val = nums[i + 1];  // 本组要重复的值
        for (int j = 0; j < freq; j++) {  // 把 val 连续写入 freq 次
            ans[k++] = val;  // 写入并后移写指针
        }
    }
    return ans;  // 返回展开后的数组（由调用方释放）
}
