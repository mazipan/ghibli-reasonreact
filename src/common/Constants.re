module Url = {
    let base = "https://ghibliapi.herokuapp.com/films";
    let get_detail_from_id = (id) => {j|$base/$id|j};
}