select distinct(c.name)
from ratings a,directors b,people c
where b.movie_id =a.movie_id
and b.person_id= c.id
and a.rating>=9.0
