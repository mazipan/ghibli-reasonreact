open Utils;

requireCSS("src/screens/detailpage/DetailPage.css");
let placeholderImage = requireAssetURI("src/assets/image/placeholder.png");

let component = ReasonReact.statelessComponent("FilmDetailPage");

module GetDetailFilm =
  Get.Make({
    type response = Model.film;
  });

let make = (~id, _children) => {
  ...component,
  render: ({state}) =>
    <div className="FilmDetailPage">
      <GetDetailFilm
        remoteUrl={Constants.Url.get_detail_from_id(id)}
        decoder=Model.read_film>
        ...{status =>
          switch (status) {
          | Idle => <p />
          | Loading => ReasonReact.string("loading")
          | Loaded(film) =>
            <div>
              {switch (film.image) {
               | Some(image) =>
                 <img
                   alt={film.title}
                   src=image
                   className="FilmDetailPage__img"
                 />
               | None => <img alt={film.title} src=placeholderImage />
               }}
              <h1 className="FilmDetailPage__title">
                <Link href="/film">
                  {ReasonReact.string(
                     "" ++ film.title ++ " (" ++ film.release_date ++ ")",
                   )}
                </Link>
              </h1>
              <div className="FilmDetailPage__director">
                {ReasonReact.string("Film by " ++ film.director)}
              </div>
              <div className="FilmDetailPage__rating">
                {ReasonReact.string("Rating " ++ film.rt_score)}
              </div>
              <div className="FilmDetailPage__desc">
                {ReasonReact.string(film.description)}
              </div>
            </div>
          | Error => ReasonReact.string("Error fetching data")
          }
        }
      </GetDetailFilm>
    </div>,
};