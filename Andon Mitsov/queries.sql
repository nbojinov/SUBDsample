 select Tag.name, Category.name from Tag,Category,Article where Tag.Article_id = Article.id and Category.id = Article.Category_id;
 select distinct User.name, Article_part2.name from Article_part1, Article_part2, User, Tag, Category where User.id = Category.User_id and Category.id = Article_part2.Category_id;

