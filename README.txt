Advance Store - C++ Container Library
=====================================

Store là std::vector nâng cao với push_front/pop_front và utility functions hữu ích.

Tác giả: Nguyễn Kỳ An(GitHub: Lurker-rpg)
Giấy phép: MIT License
🎯 CHỌN PHIÊN BẢN NÀO?
=====================

⚡ MINI VERSION (6.7 KB) - advance_store_mini.hpp
-------------------------------------------------
#include "advance/store/include/advance_store_mini.hpp"

DÙNG KHI:
• Project nhỏ, cần performance
• Chỉ cần utility functions cơ bản  
• Code base nhỏ gọn
• Làm việc với data đơn giản

TÍNH NĂNG:
✓ push_front, pop_front (ƯU ÁI so với vector)
✓ max, min, mid, sum, average
✓ contains, find, count
✓ sort, reverse, fill, unique
✓ print dễ dàng
✓ Tương thích STL algorithms

🚀 FULL VERSION (18.16 KB) - advance_store.hpp
-----------------------------------------------
#include "advance/store/include/advance_store.hpp"

DÙNG KHI:
• Enterprise applications
• Xử lý data phức tạp
• Cần error handling tốt
• Cần functional programming
• Data processing pipelines

TÍNH NĂNG BỔ SUNG:
✓ Error handling với exception
✓ Type conversion: to_int, to_double, to_char, to_string
✓ Functional: filter, transform, chainable operations
✓ Advanced iterators
✓ Memory management: reserve, shrink_to_fit
✓ Batch operations: replace_all, find_all
✓ Condition checks: any_of, all_of, none_of

📦 CÀI ĐẶT
==========

Chỉ cần copy file header vào project:
- Mini: advance_store_mini.hpp (6.7 KB)
- Full: advance_store.hpp (18.16 KB)
- Dung lượng có thể chênh lệch chút so với thực tế

📚 VÍ DỤ
========

Xem thư mục examples/:
- mini_version/:
+ mini_basic_usage.cpp      - Mini version cơ bản
+ mini_real_world.cpp       - Mini version thực tế  
- full_version/:
+ basic_usage.cpp           - Full version cơ bản
+ intermediate_operations.cpp - Full version trung bình
+ advanced_usage.cpp        - Full version nâng cao

🛠️ YÊU CẦU
===========

- C++17 trở lên
- Header-only - không cần build
- Cross-platform
- Zero dependencies

---

Store - Lựa chọn thông minh cho C++ developer!
