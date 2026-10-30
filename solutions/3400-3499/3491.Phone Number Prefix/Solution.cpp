// 3491. 电话号码前缀 / Phone Number Prefix
// 核心思路：把号码按长度升序排序，则任何前缀关系中的短串一定排在长串之前，逐个号码检查它前面所有更短的号码是否是它的前缀即可。
// 复杂度：时间 O(n log n + n * L)（L 为号码长度），空间 O(1)（不计排序开销）。
#include <ranges>  // 引入 ranges 算法与视图

class Solution {  // 定义题解类
public:  // 公有接口
    bool phonePrefix(vector<string>& numbers) {  // 主函数：判断是否不存在一个号码是另一个号码的前缀
        ranges::sort(numbers, [](const string& a, const string& b) {  // 按长度升序排序，短号码排在前面
            return a.size() < b.size();  // 长度更短者优先
        });  // 结束排序
        for (int i = 0; i < numbers.size(); i++) {  // 依次检查每个号码
            if (ranges::any_of(numbers | views::take(i), [&](const string& t) {  // 在它前面所有更短的号码中查找前缀
                    return numbers[i].starts_with(t);  // 判断是否存在前缀关系
                })) {  // 进入条件分支
                return false;  // 存在前缀关系，返回 false
            }  // 结束条件分支
        }  // 结束遍历
        return true;  // 所有号码互不为前缀，返回 true
    }  // 结束 phonePrefix
};  // 结束 Solution 类
