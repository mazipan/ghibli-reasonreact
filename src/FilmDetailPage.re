open Utils;

requireCSS("src/FilmPage.css");

type state = {
  film: option(FilmModel.film),
  loading: bool,
};

type action =
  | Loaded((FilmModel.film))
  | Loading;

let component = ReasonReact.reducerComponent("FilmDetailPage");

let make = (~id, _children) => {
  ...component,
  initialState: () => {film: None, loading: false},
  reducer: (action, state) =>
    switch (action) {
    | Loading => ReasonReact.Update({...state, loading: true})
    | Loaded((data)) =>
      ReasonReact.Update({
        film: Some(data),
        loading: false,
      });
    },
  didMount: self => {
    FilmService.fetchFilmDetail(id, data => self.send(Loaded(data)))
  },
  render: ({ state }) =>
    <div className="FilmDetailPage">
      (
        switch (state.film) {
          | Some(film) =>
            <div>
              <h1 className="FilmDetailPage__title">
                <Link href="/film">
                  { ReasonReact.string("" ++ film.title ++ " ("++  film.release_date ++")") }
                </Link>
              </h1>
              <div className="FilmDetailPage__director">
                {ReasonReact.string("Film by " ++ film.director) }
              </div>
              <div className="FilmDetailPage__rating">
                {ReasonReact.string("Rating " ++ film.rt_score) }
              </div>
              <div className="FilmDetailPage__desc">
                {ReasonReact.string(film.description) }
              </div>
            </div>
          | None => ReasonReact.string("loading")
          }
      )
    </div>,
};
