let filmBaseUrl = "https://ghibliapi.herokuapp.com/films";
let filmDetailUrl = id => {j|$filmBaseUrl/$id|j};

module Decode = {
  let film = (json): FilmModel.film => {
    let id = Json.Decode.(json |> field("id", string));
    let staticData = FilmConstant.ConstantFilm.getAdditionalData(id)
    Json.Decode.{
      id: id,
      title: json |> field("title", string),
      description: json |> field("description", string),
      director: json |> field("director", string),
      producer: json |> field("producer", string),
      release_date: json |> field("release_date", string),
      rt_score: json |> field("rt_score", string),
      imdb: Some(staticData.imdb),
      image: Some(staticData.image),
      streaming: Some(staticData.streaming)
    }
  }
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
