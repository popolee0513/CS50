select avg(a.rating)
from ratings a ,movies b
where a.movie_id=b.id
and b.year=2012