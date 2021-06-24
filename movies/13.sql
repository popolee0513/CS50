select distinct(c.name)
from stars a,movies b,people c
where a.movie_id =b.id
and a.person_id = c.id
and c.name !="Kevin Bacon"
and b.title in
(select b.title
from stars a,movies b,people c
where a.movie_id =b.id
and a.person_id = c.id
and c.name="Kevin Bacon"
and c.birth=1958)