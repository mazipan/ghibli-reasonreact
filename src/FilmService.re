let filmBaseUrl = "https://ghibliapi.herokuapp.com/films";
let filmDetailUrl = id => {j|$filmBaseUrl/$id|j};

module Decode = {
  let film = (json): FilmModel.film =>
    Json.Decode.{
      id: json |> field("id", string),
      title: json |> field("title", string),
      description: json |> field("description", string),
      director: json |> field("director", string),
      producer: json |> field("producer", string),
      release_date: json |> field("release_date", string),
      rt_score: json |> field("rt_score", string),
    };
  let films = (json): array(FilmModel.film) =>
    Json.Decode.(json |> array(film));
};

let fetchFilms = callback =>
  Js.Promise.(
    Fetch.fetch(filmBaseUrl)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.films
         |> (
           films => {
             callback(films);
             resolve();
           }
         )
       )
    |> ignore
  ); /* TODO: error handling */

let fetchFilmDetail = (id, callback) =>
  Js.Promise.(
    Fetch.fetch(filmDetailUrl(id))
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.film
         |> (
           film => {
             callback(film);
             resolve();
           }
         )
       )
    |> ignore
  ); /* TODO: error handling */
