// 题目：383. 赎金信（Ransom Note）
// 思路：用长度 26 的计数数组统计 magazine 里每个字母的库存，再逐字母扣减 ransomNote 的需求，扣成负数即失败。
// 时间复杂度：O(m + n)，m、n 分别是两串长度；空间复杂度：O(1)，只用了固定 26 个计数。
class Solution {  // 题解类
public:  // 对外接口
    bool canConstruct(string ransomNote, string magazine) {  // ransomNote 是赎金信，magazine 是杂志，判断信能否用杂志里的字母拼出
        int cnt[26]{};  // 计数桶：下标 0~25 对应 'a'~'z'，{} 保证全部初始化为 0
        for (char& c : magazine) {  // 第一趟先统计杂志里每个字母的数量
            ++cnt[c - 'a'];  // 字符减去 'a' 得到 0~25 的下标，库存加一
        }
        for (char& c : ransomNote) {  // 第二趟按赎金信逐字母消耗库存
            if (--cnt[c - 'a'] < 0) {  // 先扣减再判断：扣成负数说明这个字母不够用
                return false;  // 库存不足，立刻判定拼不出来
            }
        }
        return true;  // 所有字母都够用，可以拼出赎金信
    }
};