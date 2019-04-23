
open Utils;

requireCSS("src/FilmPage.css");
let placeholderImage = requireAssetURI("src/placeholder.png");

type state = {
  films: list(Model.film),
  loading: bool,
};

type action =
  | Loaded((list(Model.film)))
  | Loading;

let component = ReasonReact.reducerComponent("FilmPage");

module GetFilms =
  Get.Make({
    type response = list(Model.film)
  });

let make = _children => {
  ...component,
  initialState: () => {films: [], loading: false},
  reducer: (action, state) =>
    switch (action) {
    | Loading => ReasonReact.Update({...state, loading: true})
    | Loaded((data)) =>
      ReasonReact.Update({
        films: data,
        loading: false,
      });
    },
  didMount: ({send}) => {
    //FilmService.fetchData(~remoteUrl=Constants.Url.base, ~decoder=Model.read_films_response, ~callback=data => send(Loaded(data)))
    ()
  },
  render: ({ state }) =>
    <div className="FilmPage">
    <GetFilms remoteUrl=Constants.Url.base decoder=Model.read_films_response>
      ...{(status) => {
        switch(status){
          | Idle => <p></p>
          | Loaded(datas) => <p></p>
        }
      }}
    </GetFilms>
    (
      if (List.length(state.films) > 0) {
        state.films
        ->
          Model.(
            List.map(({ id, title, image, release_date})=>
              <div
                className="FilmPage__item"
                key=(id)>
                (
                  switch (image) {
                    | Some(image) => <img alt=title src=image className="FilmPage__item-img"/>
                    | None => <img alt=title src=placeholderImage />
                    }
                )
                <Link href={"/film/" ++ id} className="FilmPage__item-title">
                  <h2>{ ReasonReact.string("" ++ title ++ " ("++  release_date ++")") }</h2>
                </Link>
              </div>
            ,_))
            |> Array.of_list
            |> ReasonReact.array
      } else {
        ReasonReact.null;
      }
    )
    </div>,
};
