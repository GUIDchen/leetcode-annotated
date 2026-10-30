// 题目：3167. 字符串的更好压缩（Better Compression of String）
// 思路：一次扫描把每组「字符 + 数字串」拆开并按字符合并次数，map 天然有序，最后按字符升序重新拼接。
// 时间复杂度：O(n + k·log k)，n 为串长，k 为不同字符数（≤26）；空间复杂度：O(k)，计数表的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string betterCompression(string compressed) {  // compressed 是形如 a2b3c1 的压缩串
        map<char, int> cnt;  // 按字符有序统计出现总次数：map 的键自动升序，正好满足输出顺序
        int i = 0;  // 扫描指针，指向当前组的「字符」
        int n = compressed.length();  // 先缓存串长，循环中反复使用
        while (i < n) {  // 逐个处理「字符 + 数字串」这样的组
            char c = compressed[i];  // 当前组的字符
            int j = i + 1;  // 从字符后面开始读数字
            int x = 0;  // 当前组的次数，逐位累加到 x
            while (j < n && isdigit(compressed[j])) {  // 只要后面还是数字就继续读
                x = x * 10 + (compressed[j] - '0');  // 秦九韶算法：把字符数字逐步累积成整数
                j++;  // 后移一位
            }  // 内层读数循环结束
            cnt[c] += x;  // 同一字符的次数合并
            i = j;  // 跳到下一组的字符位置
        }  // 整个串扫描完毕
        stringstream ans;  // 用字符串流拼接结果，字符与整数都能自动转成文本
        for (const auto& entry : cnt) {  // map 已按字符升序，直接顺序遍历即可
            ans << entry.first << entry.second;  // 依次写入「字符 + 总次数」
        }  // 遍历结束
        return ans.str();  // 取出拼接好的字符串返回
    }  // 方法结束
};  // 类定义结束